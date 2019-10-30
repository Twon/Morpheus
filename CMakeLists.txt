cmake_minimum_required(VERSION 3.13)

file(STRINGS "version.txt" MORPHEUS_VERSION)

project(Morpheus
    VERSION ${MORPHEUS_VERSION}
    DESCRIPTION "A high performance focused game engine using object oriented techniques based in the latest C++"
    LANGUAGES CXX
)

option(ENABLE_CODE_COVERAGE "Enable code coverage if available (Mac OS X currently not supported)" OFF)

if (APPLE)
    SET(ENABLE_CODE_COVERAGE OFF CACHE BOOL "Ensure code coverage is switched off for Mac OS until the code coverage library addresses the AppleClang issue" FORCE)
endif()

set(BUILD_SHARED_LIBS YES)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()

conan_basic_setup(KEEP_RPATHS)

# Include necessary submodules
list(APPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/cmake/Modules
)

include(Compiler)
include(Documentation)
include(IDESettings)
include(ThirdParty)
include(Catch)

enable_testing()

#------------------------------------------------------------------------------------------------------------------------------------------
# Offer the user the choice of overriding the installation directories
include(GNUInstallDirs)
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

if (ENABLE_CODE_COVERAGE)
    coverage_evaluate()
endif()
