#[[
Copyright 2024 Antony Peacock

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
]]

include_guard(GLOBAL)

#if(MORPHEUS_ENABLE_TESTS)
    find_package(Catch2 3 REQUIRED)
    find_package(GTest REQUIRED)
    #find_package(rapidcheck REQUIRED)
#endif(MORPHEUS_ENABLE_TESTS)

find_package(Boost REQUIRED)
find_package(ctre REQUIRED)
find_package(magic_enum REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(RapidJSON REQUIRED)

if(WIN32)
    find_package(wil REQUIRED)
endif(WIN32)

#[[FetchContent_Declare(
    libunifex
    GIT_REPOSITORY git@github.com:facebookexperimental/libunifex.git
    GIT_TAG main
)
FetchContent_MakeAvailable(libunifex)]]#
