#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<print>)
    #include <print> // IWYU pragma: export
#endif // #if __has_include(<print>)

// clang-format off
#if (__cpp_lib_print >= 202207L)
    namespace morpheus { namespace print_ns = std; }
#else
    #if (__cpp_lib_format >= 201907L)
        #include <fmt/format.h> // IWYU pragma: export

        #include <format> // IWYU pragma: export

        template <typename T, typename CharT>
        requires std::formattable<T, CharT> && (!fmt::formattable<T, CharT>)
        struct fmt::formatter<T, CharT>
        {
            constexpr auto parse(format_parse_context& ctx)
            {
                return ctx.begin();
            }

            template <typename Context>
            constexpr auto format(T const& value, Context& context) const
            {
                auto const str = std::format("{}", value);
                return std::format_to(context.out(), "{}", str);
            }
        };
    #endif


    #include <fmt/core.h> // IWYU pragma: export
    namespace morpheus { namespace print_ns = fmt; }
#endif
// clang-format on
