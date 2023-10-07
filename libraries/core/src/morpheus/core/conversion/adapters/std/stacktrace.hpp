#pragma once

#include "morpheus/core/conformance/stacktrace.hpp"

#include <string_view>

// clang-format off
#if (__cpp_lib_formatters < 202302L)

template <typename Allocator>
struct morpheus::fmt_ns::formatter<morpheus::st_ns::basic_stacktrace<Allocator>> : public morpheus::fmt_ns::formatter<std::string_view>
{
    constexpr auto parse(morpheus::fmt_ns::format_parse_context& ctx)
    {
        auto pos = ctx.begin();
        return pos;  // expect `}` at this position, otherwise,
                      // it's error! exception!
    }

    auto format(const morpheus::st_ns::basic_stacktrace<Allocator>& st, morpheus::fmt_ns::format_context& ctx)
    {
        return morpheus::fmt_ns::format_to(ctx.out(), "{}", to_string(st));
    }
};

#endif
// clang-format on
