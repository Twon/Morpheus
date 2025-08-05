#[[
Copyright 2023 Antony Peacock

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

include(morpheus_add_library)
include(warnings)

morpheus_add_library(
    NAME MorpheusConfig
    ALIAS morpheus::config
    FOLDER "Libraries/Core"
    INTERFACE
)

target_link_libraries(MorpheusConfig
    INTERFACE
        $<$<PLATFORM_ID:Linux>:dl>
        std
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-stdlib=libc++>
)

target_compile_options(MorpheusConfig
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus> # https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
        $<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:${CLANG_WARNINGS}>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-stdlib=libc++> # Clang defaults to libc++ explicit to avoid picking up the system header when GCC and Clang are installed.
)

target_compile_definitions(MorpheusConfig
    INTERFACE
        MORPHEUS_MODULES_SUPPORT=$<BOOL:${MORPHEUS_MODULES_SUPPORT}>
)
