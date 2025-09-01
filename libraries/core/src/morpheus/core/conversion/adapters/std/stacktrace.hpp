#pragma once

// IWYU pragma: always_keep
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"

#include <string_view>

// clang-format off
#if (__cpp_lib_stacktrace < 202011L) or (__cpp_lib_formatters < 202302L)

template <typename Allocator>
struct morpheus::conf::fmt::formatter<morpheus::conf::st::basic_stacktrace<Allocator>>
{
    constexpr auto parse(morpheus::conf::fmt::format_parse_context& ctx) { return std::begin(ctx); }

    constexpr auto format(morpheus::conf::st::basic_stacktrace<Allocator> const& st, morpheus::conf::fmt::format_context& ctx) const
    {
        return morpheus::conf::fmt::format_to(ctx.out(), "{}", to_string(st));
    }
};

#endif
// clang-format on
