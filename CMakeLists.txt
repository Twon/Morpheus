cmake_minimum_required(VERSION 3.22)

file(STRINGS "version.txt" MORPHEUS_VERSION)

project(Morpheus
    VERSION ${MORPHEUS_VERSION}
    DESCRIPTION "A high performance focused game engine using object oriented techniques based in the latest C++"
    LANGUAGES CXX
)

cmake_policy(SET CMP0127 NEW)

#------------------------------------------------------------------------------------------------------------------------------------------
# Standard CMake Includes
include(CTest)
include(FetchContent)
include(GNUInstallDirs)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)

cmake_dependent_option(MORPHEUS_CODE_COVERAGE "Enable code coverage" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\" OR \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"GNU\"" OFF)
cmake_dependent_option(MORPHEUS_INCLUDE_NATVIS "Enable inclusion of a natvis files for debugging" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"MSVC\"" OFF)

set(BUILD_SHARED_LIBS YES)

# Include necessary submodules
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/cmake/modules
)

#------------------------------------------------------------------------------------------------------------------------------------------
# Custom CMake Includes
include(Compiler)
include(Documentation)
include(IDESettings)
include(morpheus_add_executable)
include(morpheus_add_library)
include(morpheus_add_testing_library)
include(morpheus_add_tests)
include(third_party)

enable_testing()

#------------------------------------------------------------------------------------------------------------------------------------------
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")

# Build the RPath relative to the executable locations (i.e. from the bin directory, up back to the install root and in to the lib folder.
file(RELATIVE_PATH MORPHEUS_RPATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
if (APPLE)
    set(MORPHEUS_RPATH "@executable_path/${MORPHEUS_RPATH}")
else()
    set(MORPHEUS_RPATH "$ORIGIN/${MORPHEUS_RPATH}")
endif()
file(TO_NATIVE_PATH "${MORPHEUS_RPATH}/${INSTALL_LIBDIR}" MORPHEUS_RPATH )

set(CMAKE_INSTALL_RPATH ${MORPHEUS_RPATH})
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
#------------------------------------------------------------------------------------------------------------------------------------------

add_subdirectory(libraries)
add_subdirectory(examples)

if (MORPHEUS_CODE_COVERAGE)
    coverage_evaluate()
endif()

