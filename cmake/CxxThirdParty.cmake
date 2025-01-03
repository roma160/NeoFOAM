# SPDX-License-Identifier: Unlicense
# SPDX-FileCopyrightText: 2023 NeoFOAM authors

set(NEOFOAM_KOKKOS_CHECKOUT_VERSION
    "4.3.00"
    CACHE STRING "Use specific version of Kokkos")
mark_as_advanced(NEOFOAM_KOKKOS_CHECKOUT_VERSION)

if(NEOFOAM_ENABLE_MPI_SUPPORT)
  find_package(MPI 3.1 REQUIRED)
endif()
find_package(Kokkos ${NEOFOAM_KOKKOS_CHECKOUT_VERSION} QUIET)

if(NOT ${Kokkos_FOUND})
  include(FetchContent)

  include(cmake/AutoEnableDevice.cmake)

  FetchContent_Declare(
    kokkos
    SYSTEM QUITE
    GIT_SHALLOW ON
    GIT_REPOSITORY "https://github.com/kokkos/kokkos.git"
    GIT_TAG ${NEOFOAM_KOKKOS_CHECKOUT_VERSION})

  FetchContent_MakeAvailable(Kokkos)
else()
  if(DEFINED Kokkos_ENABLE_CUDA)
    set(NEOFOAM_ENABLE_CUDA
        ON
        CACHE INTERNAL "")
  endif()
endif()

include(cmake/CPM.cmake)

cpmaddpackage(
  NAME
  cpptrace
  GITHUB_REPOSITORY
  jeremy-rifkin/cpptrace
  VERSION
  0.5.4
  SYSTEM)

cpmaddpackage(
  NAME
  nlohmann_json
  VERSION
  3.11.3
  URL
  https://github.com/nlohmann/json/releases/download/v3.11.3/include.zip
  SYSTEM)

cpmaddpackage(
  NAME
  spdlog
  GITHUB_REPOSITORY
  gabime/spdlog
  VERSION
  1.13.0
  SYSTEM)

cpmaddpackage(
  NAME
  cxxopts
  GITHUB_REPOSITORY
  jarro2783/cxxopts
  VERSION
  3.2.0
  SYSTEM)

if(NEOFOAM_BUILD_TESTS OR NEOFOAM_BUILD_BENCHMARKS)
  cpmaddpackage(
    NAME
    Catch2
    GITHUB_REPOSITORY
    catchorg/Catch2
    VERSION
    3.4.0
    SYSTEM)
endif()
