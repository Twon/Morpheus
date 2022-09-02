#pragma once

#include "core/conformance/ranges.hpp"
#include "core/gfx/concepts/video_mode.hpp"
#include "core/gfx/vendor.hpp"
#include "core/meta/concepts/string.hpp"
#include <concepts>
#include <string_view>

namespace morpheus::gfx::concepts
{

/// \concept Adapter
///     Adapters define the underlying graphics API abstraction of the underlying graphic hardware device. 
template <typename T>
concept Adapter = requires(T t)
{
    { t.getId() } -> std::equality_comparable;
    { t.getName() } -> meta::ConvertableToStringView;
    { t.getVendor() } -> std::same_as<Vendor>;
    { t.getVideoModes() } -> VideoModeRange;
};

template <typename T>
concept AdapterRange = Adapter<ranges::range_value_t<T>>;

} // namespace morpheus::gfx::concepts
