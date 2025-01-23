# SPDX-License-Identifier: Unlicense
# SPDX-FileCopyrightText: 2024 NeoFOAM authors

if(NEOFOAM_ENABLE_MPI_SUPPORT)
  add_subdirectory(mpi)
endif()

add_subdirectory(primitives)
add_subdirectory(database)

neofoam_unit_test(dictionary)
neofoam_unit_test(tokenList)
neofoam_unit_test(input)
neofoam_unit_test(executor)
neofoam_unit_test(parallelAlgorithms)

function(configure_custom_test TARGET)
  if(WIN32)
    set_target_properties(
      ${TARGET}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/$<0:>
                 LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/$<0:>
                 ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/$<0:>)

  else()
    set_property(TARGET ${TARGET} PROPERTY RUNTIME_OUTPUT_DIRECTORY
                                           ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
  endif()

  copy_target_dlls(${TARGET})
endfunction()

add_executable(runTimeSelectionFactory "runTimeSelectionFactory.cpp")
target_link_libraries(runTimeSelectionFactory PRIVATE Catch2::Catch2WithMain cpptrace::cpptrace
                                                      NeoFOAM)

configure_custom_test(runTimeSelectionFactory)

add_test(
  NAME runTimeSelectionFactory
  COMMAND runTimeSelectionFactory
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)

add_library(sharedExtensionLib SHARED)
target_sources(sharedExtensionLib PRIVATE "sharedExtensionLib.cpp")
target_link_libraries(sharedExtensionLib PRIVATE NeoFOAM_public_api cpptrace::cpptrace NeoFOAM)
configure_custom_test(sharedExtensionLib)

add_executable(sharedRunTimeSelectionFactory "sharedRunTimeSelectionFactory.cpp")
target_link_libraries(sharedRunTimeSelectionFactory
                      PRIVATE Catch2::Catch2WithMain cpptrace::cpptrace NeoFOAM sharedExtensionLib)
configure_custom_test(sharedRunTimeSelectionFactory)

add_test(
  NAME sharedRunTimeSelectionFactory
  COMMAND sharedRunTimeSelectionFactory
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
