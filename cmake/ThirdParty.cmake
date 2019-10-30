include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
)

FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
    list(APPEND CMAKE_MODULE_PATH
        ${catch2_SOURCE_DIR}/contrib
    )
endif()

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
    FetchContent_Populate(fmt)
    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()

FetchContent_Declare(
    codecoverage
    GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov.git
)

FetchContent_GetProperties(codecoverage)
if(NOT codecoverage_POPULATED)
    FetchContent_Populate(codecoverage)
    list(APPEND CMAKE_MODULE_PATH ${codecoverage_SOURCE_DIR}/cmake)
endif()

set(ENABLE_COVERAGE ${ENABLE_CODE_COVERAGE} CACHE BOOL "Enable coverage build." FORCE)
find_package(codecov)

if (ENABLE_CODE_COVERAGE)
    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
    list(APPEND LCOV_REMOVE_PATTERNS "'${CMAKE_CURRENT_BINARY_DIR}/*'")
	set_target_properties(gcov lcov-capture lcov-capture-init lcov-genhtml PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})
endif()
