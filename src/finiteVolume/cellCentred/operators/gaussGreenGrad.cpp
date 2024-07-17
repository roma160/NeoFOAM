// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#include <functional>

#include "NeoFOAM/finiteVolume/cellCentred/operators/gaussGreenGrad.hpp"
#include "NeoFOAM/finiteVolume/cellCentred/interpolation/linear.hpp"
#include "NeoFOAM/core/parallelAlgorithms.hpp"

namespace NeoFOAM::finiteVolume::cellCentred
{

void computeGrad(
    const VolumeField<scalar>& phi,
    const SurfaceInterpolation& surfInterp,
    VolumeField<Vector>& gradPhi
)
{
    const UnstructuredMesh& mesh = gradPhi.mesh();
    const auto exec = gradPhi.exec();
    SurfaceField<scalar> phif(exec, mesh, createCalculatedBCs<scalar>(mesh));
    const auto surfFaceCells = mesh.boundaryMesh().faceCells().span();
    const auto s_bSf = mesh.boundaryMesh().sf().span();
    auto surfGradPhi = gradPhi.internalField().span();

    surfInterp.interpolate(phif, phi);
    const auto surfPhif = phif.internalField().span();
    const auto surfOwner = mesh.faceOwner().span();
    const auto surfNeighbour = mesh.faceNeighbour().span();
    const auto s_Sf = mesh.faceAreas().span();
    size_t nInternalFaces = mesh.nInternalFaces();

    const auto surfV = mesh.cellVolumes().span();

    if (std::holds_alternative<CPUExecutor>(exec))
    {
        for (size_t i = 0; i < nInternalFaces; i++)
        {
            Vector Flux = s_Sf[i] * surfPhif[i];
            surfGradPhi[surfOwner[i]] += Flux;
            surfGradPhi[surfNeighbour[i]] -= Flux;
        }

        for (size_t i = nInternalFaces; i < surfPhif.size(); i++)
        {
            int32_t own = surfFaceCells[i - nInternalFaces];
            Vector valueOwn = s_bSf[i - nInternalFaces] * surfPhif[i];
            surfGradPhi[own] += valueOwn;
        }

        for (size_t celli = 0; celli < mesh.nCells(); celli++)
        {
            surfGradPhi[celli] *= 1 / surfV[celli];
        }
    }
    else
    {
        parallelFor(
            exec,
            {0, nInternalFaces},
            KOKKOS_LAMBDA(const size_t i) {
                Vector Flux = s_Sf[i] * surfPhif[i];
                Kokkos::atomic_add(&surfGradPhi[surfOwner[i]], Flux);
                Kokkos::atomic_sub(&surfGradPhi[surfNeighbour[i]], Flux);
            }
        );

        parallelFor(
            exec,
            {nInternalFaces, surfPhif.size()},
            KOKKOS_LAMBDA(const size_t i) {
                size_t own = surfFaceCells[i - nInternalFaces];
                Vector valueOwn = s_Sf[i] * surfPhif[i];
                Kokkos::atomic_add(&surfGradPhi[own], valueOwn);
            }
        );

        parallelFor(
            exec,
            {0, mesh.nCells()},
            KOKKOS_LAMBDA(const size_t celli) { surfGradPhi[celli] *= 1 / surfV[celli]; }
        );
    }
}

gaussGreenGrad::gaussGreenGrad(const Executor& exec, const UnstructuredMesh& mesh)
    : mesh_(mesh), surfaceInterpolation_(exec, mesh, std::make_unique<Linear>(exec, mesh)) {};


void gaussGreenGrad::grad(VolumeField<Vector>& gradPhi, const VolumeField<scalar>& phi)
{
    computeGrad(phi, surfaceInterpolation_, gradPhi);
};

} // namespace NeoFOAM
