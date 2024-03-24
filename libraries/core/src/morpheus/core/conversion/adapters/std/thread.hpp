#pragma once

#include "morpheus/core/conformance/format.hpp"

#include <thread>
#include <sstream>

// clang-format off
#if (__cpp_lib_formatters < 202302L)

template <typename charT>
struct std::formatter<std::thread::id, charT>
{
    constexpr auto parse(morpheus::fmt_ns::format_parse_context& ctx) { return std::begin(ctx); }

    constexpr auto format(std::thread:id const& id, morpheus::fmt_ns::format_context& ctx) const
    {
        std::stringstream str;
        str << id;
        return morpheus::fmt_ns::format_to(ctx.out(), "{}", str.str());
    }
};

#endif
// clang-format on
