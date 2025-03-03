Installation
============

You can install NeoFOAM by following these steps:

Clone the NeoFOAM repository:

   .. code-block:: bash

      git clone https://github.com/exasim-project/NeoFOAM.git

Navigate to the NeoFOAM directory:

   .. code-block:: bash

      cd NeoFOAM

NeoFOAM uses CMake to build, thus the standard CMake procedure should work, however, we recommend using one of the provided CMake presets detailed below `below <Building with CMake Presets>`_. From a build directory, you can execute:

   .. code-block:: bash

        mkdir build
        cd build
        cmake <DesiredBuildFlags> ..
        cmake --build .
        cmake --install .

The following can be chained with -D<DesiredBuildFlags>=<Value> to the CMake command most and most relevant build flags are:

+---------------------------+-----------------------------------+---------+
| Flag                      | Description                       | Default |
+===========================+===================================+=========+
| CMAKE_BUILD_TYPE          | Build in debug or release mode    | Debug   |
+---------------------------+-----------------------------------+---------+
| NEOFOAM_BUILD_APPS        | Build NeoFOAM with Applications   | ON      |
+---------------------------+-----------------------------------+---------+
| NEOFOAM_BUILD_BENCHMARKS  | Build NeoFOAM with benchmarks     | OFF     |
+---------------------------+-----------------------------------+---------+
| NEOFOAM_BUILD_DOC         | Build NeoFOAM with documentation  | ON      |
+---------------------------+-----------------------------------+---------+
| NEOFOAM_BUILD_TESTS       | Build NeoFOAM with tests          | OFF     |
+---------------------------+-----------------------------------+---------+
| Kokkos_ENABLE_SERIAL      | Enable Serial backend for Kokkos  | ON      |
+---------------------------+-----------------------------------+---------+
| Kokkos_ENABLE_OPENMP      | Enable OpenMP backend for Kokkos  | ON      |
+---------------------------+-----------------------------------+---------+
| Kokkos_ENABLE_HIP         | Enable HIP backend for Kokkos     | OFF     |
+---------------------------+-----------------------------------+---------+
| Kokkos_ENABLE_SYCL        | Enable SYCL backend for Kokkos    | OFF     |
+---------------------------+-----------------------------------+---------+
| Kokkos_ENABLE_CUDA        | Enable CUDA backend for Kokkos    | OFF     |
+---------------------------+-----------------------------------+---------+

By opening the the project with cmake-gui you can easily set these flags and configure the build.

.. note::

   NeoFOAM will automatically enable ``Kokkos_ENABLE_CUDA`` or ``Kokkos_ENABLE_HIP`` if either of this is available on
   the system. This can be prevented by setting both options explicitly.

Building with CMake Presets
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Additionally, we provide several CMake presets to set commonly required flags if you compile NeoFoam in combination with Kokkos.

   .. code-block:: bash

    cmake --list-presets # To list existing presets

To build NeoFOAM for production use, you can use the following commands:

   .. code-block:: bash

    cmake --preset production # To configure with ninja and common kokkos flags
    cmake --build --preset production # To compile with ninja and common kokkos flags

It should be noted that the build directory changes depending on the chosen preset. This way you can have different build directories for different presets and easily switch between them.

Prerequisites
^^^^^^^^^^^^^

The following tools are used in the development of this project:

required tools for documentation:
.. code-block:: bash

    sudo apt install doxygen
    pip install pre-commit sphinx furo breathe sphinx-sitemap


required tools for compilation (ubuntu latest 24.04):

.. code-block:: bash

    sudo apt update
    sudo apt install \
    ninja-build \
    clang-16 \
    gcc-10 \
    libomp-16-dev \
    python3 \
    python3-dev \
    build-essential
    # installation of clang is optional
    sudo apt remove clang-14
    sudo rm /usr/bin/clang
    sudo rm /usr/bin/clang++
    sudo ln -s /usr/bin/clang-16 /usr/bin/clang
    sudo ln -s /usr/bin/clang++-16 /usr/bin/clang++

Windows
"""""""

To compile NeoFOAM on windows, mysys2 is required the installation is described in vscode user guide_

.. _guide: https://code.visualstudio.com/docs/cpp/config-mingw


Following package are required with pacman

.. code-block:: bash

   #pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
   pacman -S mingw-w64-x86_64-clang
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-ninja
   pacman -S mingw-w64-x86_64-msmpi

   pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-msmpi mingw-w64-x86_64-python mingw-w64-x86_64-lld


It also requires the addition of following User Path variables (see vscode guide), assuming the default installation path

.. code-block:: bash

   C:\msys64\mingw64\bin

in vscode make sure clang (the current version of gcc installed with pacman is only 14.0 (7.9.24)) is selected by adding to set .vscode/settings.json

  "cmake.environment": {
    "CC": "clang",
    "CXX": "clang++"
  }




Workflow with vscode
^^^^^^^^^^^^^^^^^^^^

install the following extensions:

.. code-block:: bash

   ms-vscode.cpptools
   ms-vscode.cmake-tools


After installation, you can open the NeoFOAM directory with vscode and configure the build with cmake presets with the cmake extension as shown below:

.. figure:: _static/installation/cmakePresets.gif
   :alt: configure the build with cmake presets
   :align: center

After configuring the build, you can build the project with the build button or test in "testing" tab (flask icon).

To create the documentation, you can use the 'Build Sphinx Documentation' task in the vscode task menu. Type `Ctrl+P` and type `task` and press space and the build documentation and press enter. The documentation will be created in the `docs_build` directory.
