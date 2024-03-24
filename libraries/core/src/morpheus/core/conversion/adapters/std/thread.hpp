#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <thread>

// clang-format off
#if (__cpp_lib_formatters < 202302L)

template <typename charT>
struct morpheus::fmt_ns::formatter<std::thread::id, charT>
{
    constexpr auto parse(morpheus::fmt_ns::format_parse_context& ctx) { return std::begin(ctx); }

    constexpr auto format(std::thread::id const& id, morpheus::fmt_ns::format_context& ctx) const
    {
#if MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER
        return morpheus::fmt_ns::format_to(ctx.out(), "{}", id._Get_underlying_id());
#elif (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
        if constexpr (sizeof(id) == sizeof(std::uint64_t))
            auto const idAsInt = *reinterpret_cast<std::uint64_t const*>(&id);
            return morpheus::fmt_ns::format_to(ctx.out(), "{}", idAsInt);
        else
            auto const idAsInt = *reinterpret_cast<std::uint32_t const*>(&id);
            return morpheus::fmt_ns::format_to(ctx.out(), "{}", idAsInt);
#else
    #error "Compiler unsupported for fallback std::formatter<std::thread::id> support"
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    }
};

#endif
// clang-format on
