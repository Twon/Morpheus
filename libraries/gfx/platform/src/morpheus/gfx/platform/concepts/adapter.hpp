#pragma once

#include "morpheus/gfx/platform/concepts/video_mode.hpp"
#include "morpheus/gfx/platform/vendor.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/meta/concepts/string.hpp"
#include <concepts>
#include <string_view>

namespace morpheus::gfx::concepts
{

/// \concept Adapter
///     Adapters define the underlying graphics API abstraction of the underlying graphic hardware device.
template <typename T>
concept Adapter = requires(T t)
{
    { t.id() } -> std::equality_comparable;
    { t.name() } -> meta::ConvertableToStringView;
    { t.vendor() } -> std::same_as<Vendor>;
//    { t.getVideoModes() } -> VideoModeRange;
};

template <typename T>
concept AdapterRange = Adapter<ranges::range_value_t<T>>;

} // namespace morpheus::gfx::concepts
