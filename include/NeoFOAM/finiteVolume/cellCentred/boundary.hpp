// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 NeoFOAM authors

#pragma once

#include "boundary/volume/empty.hpp"
#include "boundary/volume/calculated.hpp"
#include "boundary/volume/fixedValue.hpp"
#include "boundary/volume/fixedGradient.hpp"

#include "boundary/surface/empty.hpp"
#include "boundary/surface/calculated.hpp"
#include "boundary/surface/fixedValue.hpp"

#include "NeoFOAM/lib_api.h"

namespace NeoFOAM
{

namespace fvcc = finiteVolume::cellCentred;

template class NeoFOAM_API fvcc::VolumeBoundaryFactory<scalar>;
template class NeoFOAM_API fvcc::VolumeBoundaryFactory<Vector>;

template class NeoFOAM_API fvcc::volumeBoundary::FixedValue<scalar>;
template class NeoFOAM_API fvcc::volumeBoundary::FixedValue<Vector>;

template class NeoFOAM_API fvcc::volumeBoundary::FixedGradient<scalar>;
template class NeoFOAM_API fvcc::volumeBoundary::FixedGradient<Vector>;

template class NeoFOAM_API fvcc::volumeBoundary::Calculated<scalar>;
template class NeoFOAM_API fvcc::volumeBoundary::Calculated<Vector>;

template class NeoFOAM_API fvcc::volumeBoundary::Empty<scalar>;
template class NeoFOAM_API fvcc::volumeBoundary::Empty<Vector>;

template class NeoFOAM_API fvcc::SurfaceBoundaryFactory<scalar>;
template class NeoFOAM_API fvcc::SurfaceBoundaryFactory<Vector>;

template class NeoFOAM_API fvcc::surfaceBoundary::FixedValue<scalar>;
template class NeoFOAM_API fvcc::surfaceBoundary::FixedValue<Vector>;

template class NeoFOAM_API fvcc::surfaceBoundary::Calculated<scalar>;
template class NeoFOAM_API fvcc::surfaceBoundary::Calculated<Vector>;

template class NeoFOAM_API fvcc::surfaceBoundary::Empty<scalar>;
template class NeoFOAM_API fvcc::surfaceBoundary::Empty<Vector>;

}
