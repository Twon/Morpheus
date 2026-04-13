#pragma once

#include "morpheus/core/conformance/scan.hpp"

#include <concepts>
#include <type_traits>

namespace morpheus::meta::concepts::detail
{

template <class T, class Context, class Scanner = typename Context::template scanner_type<std::remove_const_t<T>>>
concept ScannableWith = std::semiregular<Scanner> &&
                        requires(Scanner& s, Scanner const& cs, T& t, Context& ctx, conf::scan::basic_scan_parse_context<typename Context::char_type> pctx) {
                            { s.parse(pctx) } -> std::same_as<typename decltype(pctx)::iterator>;
                            { cs.scan(t, ctx) } -> std::same_as<conf::scan::scan_expected<typename Context::iterator>>;
                        };

} // namespace morpheus::meta::concepts::detail
