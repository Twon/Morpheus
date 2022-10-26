include(FetchContent)


find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(indirect_value REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(range-v3 REQUIRED)

FetchContent_Declare(
    codecoverage
    GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov.git
)

FetchContent_GetProperties(codecoverage)
if(NOT codecoverage_POPULATED)
    FetchContent_Populate(codecoverage)
    list(APPEND CMAKE_MODULE_PATH ${codecoverage_SOURCE_DIR}/cmake)
endif()

set(ENABLE_COVERAGE ${MORPHEUS_CODE_COVERAGE} CACHE BOOL "Enable coverage build." FORCE)
find_package(codecov)

if (ENABLE_CODE_COVERAGE)
    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
    list(APPEND LCOV_REMOVE_PATTERNS "'${CMAKE_CURRENT_BINARY_DIR}/*'")
	set_target_properties(gcov lcov-capture lcov-capture-init lcov-genhtml PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})
endif()
