cmake_minimum_required(VERSION 3.13.0)

file(STRINGS "version.txt" MORPHEUS_VERSION)

project(Morpheus
    VERSION ${MORPHEUS_VERSION}
    DESCRIPTION "A high performance focused game engine using object oriented techniques based in the latest C++"
    LANGUAGES CXX
)

set(BUILD_SHARED_LIBS YES)

# Include necessary submodules
set(CMAKE_MODULE_PATH
    "${CMAKE_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/cmake"
    "${PROJECT_SOURCE_DIR}/cmake/Modules"
)

include(Compiler)
include(Documentation)
include(IDESettings)
include(ThirdParty)

enable_testing()

add_subdirectory(libraries)
add_subdirectory(examples)
