include_guard(GLOBAL)

include(FetchContent)

find_package(Catch2 3 REQUIRED)
find_package(GTest REQUIRED)
find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(Microsoft.GSL REQUIRED)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    find_package(date REQUIRED)
endif (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY https://github.com/jbcoe/polymorphic_value.git
    GIT_TAG main
)
FetchContent_MakeAvailable(polymorphic_value)

if(WIN32)
    set(WIL_BUILD_TESTS OFF)
    FetchContent_Declare(
        wil
        GIT_REPOSITORY https://github.com/microsoft/wil.git
    )
    FetchContent_MakeAvailable(wil)
endif()

#[[FetchContent_Declare(
    libunifex
    GIT_REPOSITORY git@github.com:facebookexperimental/libunifex.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(libunifex)]]#

#set(ENABLE_COVERAGE ${MORPHEUS_CODE_COVERAGE} CACHE BOOL "Enable coverage build." FORCE)
#find_package(codecov)

#if (ENABLE_CODE_COVERAGE)
#    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
#    list(APPEND LCOV_REMOVE_PATTERNS "'${CMAKE_CURRENT_BINARY_DIR}/*'")
#	set_target_properties(gcov lcov-capture lcov-capture-init lcov-genhtml PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})
#endif()
