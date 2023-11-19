#pragma once

#include <morpheus/core/base/compiler.hpp>

#include <utility>

namespace morpheus
{

[[noreturn]] inline void unreachable() noexcept
{
#if (__cpp_lib_unreachable >= 202202L)
    std::unreachable();
#elif (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
    __builtin_unreachable();
#elif (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    __assume(false);
#endif
}

}
