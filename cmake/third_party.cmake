include_guard(GLOBAL)

include(FetchContent)

# if(MORPHEUS_ENABLE_TESTS)
find_package(Catch2 3 REQUIRED)
find_package(GTest REQUIRED)
# find_package(rapidcheck REQUIRED) endif(MORPHEUS_ENABLE_TESTS)

find_package(Boost REQUIRED)
find_package(ctre REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(RapidJSON REQUIRED)

if(WIN32)
    find_package(wil REQUIRED)
endif(WIN32)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    find_package(date REQUIRED)
endif(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

#[[FetchContent_Declare(
    libunifex
    GIT_REPOSITORY git@github.com:facebookexperimental/libunifex.git
    GIT_TAG main
)
FetchContent_MakeAvailable(libunifex)]]
#
