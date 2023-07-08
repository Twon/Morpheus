include_guard(GLOBAL)

include(FetchContent)

find_package(Catch2 3 REQUIRED)
find_package(GTest REQUIRED)
find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(Microsoft.GSL REQUIRED)

if(WIN32)
    find_package(wil REQUIRED)
endif(WIN32)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    find_package(date REQUIRED)
endif (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

FetchContent_Declare(polymorphic_value
    GIT_REPOSITORY https://github.com/jbcoe/polymorphic_value.git
    GIT_TAG main
)
FetchContent_MakeAvailable(polymorphic_value)

#[[FetchContent_Declare(
    libunifex
    GIT_REPOSITORY git@github.com:facebookexperimental/libunifex.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(libunifex)]]#
