#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"

#include <string_view>

// clang-format off
#if (__cpp_lib_stacktrace < 202011L) or (__cpp_lib_formatters < 202302L)

template <typename Allocator>
struct morpheus::fmt_ns::formatter<morpheus::st_ns::basic_stacktrace<Allocator>>
{
    constexpr auto parse(morpheus::fmt_ns::format_parse_context& ctx) { return std::begin(ctx); }

    constexpr auto format(morpheus::st_ns::basic_stacktrace<Allocator> const& st, morpheus::fmt_ns::format_context& ctx) const
    {
        return morpheus::fmt_ns::format_to(ctx.out(), "{}", to_string(st));
    }
};

#endif
// clang-format on
