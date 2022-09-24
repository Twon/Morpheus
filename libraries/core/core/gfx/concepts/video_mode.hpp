#pragma once

#include "core/conformance/ranges.hpp"
#include <concepts>

namespace morpheus::gfx::concepts
{

template <typename T>
concept VideoMode = requires(T t)
{
    { t.width() } -> std::convertible_to<std::uint32_t>;
    { t.height() } -> std::convertible_to<std::uint32_t>;
    { t.colourDepth() } -> std::convertible_to<std::uint32_t>;
    { t.refreshRate() } -> std::convertible_to<std::uint32_t>;
};

template <typename T>
concept VideoModeRange = VideoMode<ranges::range_value_t<T>>;

} // namespace morpheus::gfx::concepts
