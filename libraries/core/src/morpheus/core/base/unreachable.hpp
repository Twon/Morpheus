#pragma once

#include <morpheus/core/base/compiler.hpp>

/// \def MORPHEUS_UNREACHABLE
///     Macro which can be used to signify to the compiler that
///     - The programmer knows code following can never be executed (so dead code elimination can be performed).
///     - Linearize code (remove branches) by knowing that a path is cold (similar to calling [[noreturn]] function).
#if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
#   define MORPHEUS_UNREACHABLE __assume(0)
#elif (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
#   define MORPHEUS_UNREACHABLE __builtin_unreachable()
#else
#   define MORPHEUS_UNREACHABLE void()
#endif
