#pragma once

#include <morpheus/core/base/compiler.hpp>
#include <utility>

///  Function to signify to the compiler that
///     - The programmer knows code following can never be executed (so dead code elimination can be performed).
///     - Linearize code (remove branches) by knowing that a path is cold (similar to calling [[noreturn]] function).
///  \note
///      Conformance wrapper for https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0627r6.pdf
// clang-format off
#if (__cpp_lib_unreachable >= 202202L)
    [[noreturn]] inline void unreachable() { std::unreachable(); }
#else
    #if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
        [[noreturn]] inline void unreachable() { __assume(false); }
    #elif (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
        [[noreturn]] inline void unreachable() { __builtin_unreachable(); }
    #else
        [[noreturn]] inline void unreachable() {}
    #endif
#endif
// clang-format on
