cmake_minimum_required(VERSION 3.14)

project(scran_blocks
    VERSION 0.1.1
    DESCRIPTION "Blocking utilities for libscran"
    LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Library
add_library(scran_blocks INTERFACE)
add_library(libscran::scran_blocks ALIAS scran_blocks)

target_include_directories(scran_blocks INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/scran_blocks>)
target_compile_features(scran_blocks INTERFACE cxx_std_17)

# Dependencies
option(SCRAN_MARKERS_FETCH_EXTERN "Automatically fetch scran_blocks's external dependencies." ON)
if(SCRAN_MARKERS_FETCH_EXTERN)
    add_subdirectory(extern)
else()
    find_package(ltla_sanisizer 0.1.0 CONFIG REQUIRED)
endif()

target_link_libraries(scran_blocks INTERFACE ltla::sanisizer)

# Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(SCRAN_BLOCKS_TESTS "Build scran_blocks's test suite." ON)
else()
    option(SCRAN_BLOCKS_TESTS "Build scran_blocks's test suite." OFF)
endif()

if(SCRAN_BLOCKS_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif() 
endif()

# Install
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scran_blocks)

install(TARGETS scran_blocks
    EXPORT scran_blocksTargets)

install(EXPORT scran_blocksTargets
    FILE libscran_scran_blocksTargets.cmake
    NAMESPACE libscran::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libscran_scran_blocks)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/libscran_scran_blocksConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libscran_scran_blocks)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libscran_scran_blocksConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libscran_scran_blocksConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libscran_scran_blocksConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libscran_scran_blocks)
