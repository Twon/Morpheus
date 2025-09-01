#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/format.hpp"

#include <thread>

// clang-format off
#if (__cpp_lib_formatters < 202302L)

template <typename charT>
struct morpheus::conf::fmt::formatter<std::thread::id, charT>
{
    constexpr auto parse(morpheus::conf::fmt::format_parse_context& ctx) { return std::begin(ctx); }

    constexpr auto format(std::thread::id const& id, morpheus::conf::fmt::format_context& ctx) const
    {
#if MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER
        return morpheus::conf::fmt::format_to(ctx.out(), "{}", id._Get_underlying_id());
#elif (MORPHEUS_COMPILER == MORPHEUS_APPLE_CLANG_COMPILER)
        auto const idAsInt = *reinterpret_cast<std::uint64_t const*>(&id);
        return morpheus::conf::fmt::format_to(ctx.out(), "{:#x}", idAsInt);
#elif (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
        if constexpr (sizeof(id) == sizeof(std::uint64_t))
        {
            auto const idAsInt = *reinterpret_cast<std::uint64_t const*>(&id);
            return morpheus::conf::fmt::format_to(ctx.out(), "{}", idAsInt);
        }
        else if constexpr (sizeof(id) == sizeof(std::uint32_t))
        {
            auto const idAsInt = *reinterpret_cast<std::uint32_t const*>(&id);
            return morpheus::conf::fmt::format_to(ctx.out(), "{}", idAsInt);
        }
        else
            static_assert(sizeof(id) == sizeof(std::uint32_t) || sizeof(id) == sizeof(std::uint64_t), "Expected size is 32 or 64-bits only. Extend support if required");
#else
    #error "Compiler unsupported for fallback std::formatter<std::thread::id> support"
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    }
};

#endif
// clang-format on
