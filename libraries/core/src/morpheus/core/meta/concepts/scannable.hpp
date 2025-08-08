#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/meta/detail/scannable.hpp"

#include <type_traits>

namespace morpheus::meta::concepts
{

/// \concept Scannable
///     Verifies a given T is a scannable type.
template <class T, class CharT>
concept Scannable =
    detail::ScannableWith<std::remove_reference_t<T>, scan_ns::basic_scan_context<morpheus::ranges::subrange<CharT const*, CharT const*>, CharT>>;

} // namespace morpheus::meta::concepts
