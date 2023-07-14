#pragma once

#include <morpheus/core/base/compiler.hpp>

/// \def MORPHEUS_FUNCTION_COLD
///     Macro which can be used to signify to the compiler that
///     - The following function should be considered on the cold path and the compiler and optimise accordingly
#if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
    #define MORPHEUS_FUNCTION_COLD __attribute__((cold))
#elif (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER)
    #define MORPHEUS_FUNCTION_COLD [[gnu::cold]]
#else
    #define MORPHEUS_FUNCTION_COLD
#endif