cmake_minimum_required(VERSION 3.14)

project(scran_utils
    VERSION 1.0.0
    DESCRIPTION "Aggregate expression values across cells"
    LANGUAGES CXX)

add_library(scran_utils INTERFACE)
target_compile_features(scran_utils INTERFACE cxx_std_17)
target_include_directories(scran_utils INTERFACE include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
