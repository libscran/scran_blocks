cmake_minimum_required(VERSION 3.14)

project(scran_utils
    VERSION 1.0.0
    DESCRIPTION "Core utilities for libscran"
    LANGUAGES CXX)

add_library(scran_core_utils INTERFACE)
target_compile_features(scran_core_utils INTERFACE cxx_std_17)
target_include_directories(scran_core_utils INTERFACE include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()

add_library(scran_core_utils_internal INTERFACE)
target_compile_features(scran_core_utils_internal INTERFACE cxx_std_17)
target_include_directories(scran_core_utils_internal INTERFACE include/scran)
