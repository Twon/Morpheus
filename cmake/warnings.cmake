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

include_guard(GLOBAL)

set(MSVC_WARNINGS
    /permissive- # standards conformance.
    /W4 # Level 1, 2, 3 and 4 warnings.
)

set(GCC_CLANG_COMPATIBLE_WARNINGS
    -Wall
    -Wextra
    -Wextra-semi # Warn on extra semi-colon ourside of a function
    -Wimplicit-fallthrough # Warn on statement fallthrough without explicit annotation.
    -Wmisleading-indentation # Warn on misleading indentation.
    -Wmissing-include-dirs # Warn if a user-supplied include directory does not exist.
    -Wnull-dereference # Warn on null pointer dereference.
    -Wpedantic # Standard conformance.
    -Wshadow # Warning of a variabled shadows the declation of one from the parent context.
)

set(GCC_WARNINGS
   ${GCC_CLANG_COMPATIBLE_WARNINGS}
)

set(CLANG_WARNINGS
   ${GCC_CLANG_COMPATIBLE_WARNINGS}
    -Wextra-semi-stmt # warn about empty expression statements, for example extra ; like this: puts("string");;
)
