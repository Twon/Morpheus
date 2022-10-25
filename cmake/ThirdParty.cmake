include(FetchContent)

find_package(Boost REQUIRED COMPONENTS test)
find_package(Catch2 3 REQUIRED)
find_package(indirect_value REQUIRED)
find_package(Microsoft.GSL REQUIRED)

FetchContent_Declare(
    codecoverage
    GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov.git
)

FetchContent_GetProperties(codecoverage)
if(NOT codecoverage_POPULATED)
    FetchContent_Populate(codecoverage)
    list(APPEND CMAKE_MODULE_PATH ${codecoverage_SOURCE_DIR}/cmake)
endif()

if(WIN32)
    set(WIL_BUILD_TESTS OFF CACHE BOOL "Sets option to build the unit tests, default on" FORCE)
#    option(WIL_BUILD_TESTS "Sets option to build the unit tests, default on" ON)
    FetchContent_Declare(
        wil
        GIT_REPOSITORY git@github.com:microsoft/wil.git
    )
    FetchContent_MakeAvailable(wil)
endif()

#[[FetchContent_Declare(
    libunifex
    GIT_REPOSITORY git@github.com:facebookexperimental/libunifex.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(libunifex)]]#

set(ENABLE_COVERAGE ${MORPHEUS_CODE_COVERAGE} CACHE BOOL "Enable coverage build." FORCE)
find_package(codecov)

if (ENABLE_CODE_COVERAGE)
    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
    list(APPEND LCOV_REMOVE_PATTERNS "'${CMAKE_CURRENT_BINARY_DIR}/*'")
	set_target_properties(gcov lcov-capture lcov-capture-init lcov-genhtml PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})
endif()
