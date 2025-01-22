// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#pragma once

#include <Kokkos_Core.hpp>

#include "NeoFOAM/fields/field.hpp"
#include "NeoFOAM/finiteVolume/cellCentred/boundary/surfaceBoundaryFactory.hpp"
#include "NeoFOAM/mesh/unstructured.hpp"
#include "NeoFOAM/core/parallelAlgorithms.hpp"

namespace NeoFOAM::finiteVolume::cellCentred::surfaceBoundary
{
namespace detail
{
// Without this function the compiler warns that calling a __host__ function
// from a __device__ function is not allowed
template<typename ValueType>
void setFixedValue(
    DomainField<ValueType>& domainField,
    const UnstructuredMesh& mesh,
    std::pair<size_t, size_t> range,
    ValueType fixedValue
)
{
    auto refValue = domainField.boundaryField().refValue().span();
    auto value = domainField.boundaryField().value().span();
    auto internalValues = domainField.internalField().span();
    auto nInternalFaces = mesh.nInternalFaces();

    NeoFOAM::parallelFor(
        domainField.exec(),
        range,
        KOKKOS_LAMBDA(const size_t i) {
            refValue[i] = fixedValue;
            value[i] = fixedValue;
            internalValues[nInternalFaces + i] = fixedValue;
        }
    );
}
}

template<typename ValueType>
class FixedValue :
    public SurfaceBoundaryFactory<ValueType>::template Register<FixedValue<ValueType>>
{
    using Base = SurfaceBoundaryFactory<ValueType>::template Register<FixedValue<ValueType>>;

public:

    FixedValue(const UnstructuredMesh& mesh, const Dictionary& dict, std::size_t patchID)
        : Base(mesh, dict, patchID), mesh_(mesh), fixedValue_(dict.get<ValueType>("fixedValue"))
    {}

    virtual void correctBoundaryCondition(DomainField<ValueType>& domainField) override
    {
        detail::setFixedValue(domainField, mesh_, this->range(), fixedValue_);
    }

    static std::string name() { return "fixedValue"; }

    static std::string doc() { return "Set a fixed value on the boundary"; }

    static std::string schema() { return "none"; }

    virtual std::unique_ptr<SurfaceBoundaryFactory<ValueType>> clone() const override
    {
        return std::make_unique<FixedValue>(*this);
    }

private:

    const UnstructuredMesh& mesh_;
    ValueType fixedValue_;
};

}
