#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include <concepts>

namespace morpheus::gfx::concepts
{

/// \concept RenderWindow
///
template <typename T>
concept RenderWindow = requires(T t)
{
    typename T::WindowHandle;
    { t.width() } -> std::convertible_to<std::uint32_t>;
    { t.height() } -> std::convertible_to<std::uint32_t>;
    { t.colourDepth() } -> std::convertible_to<std::uint32_t>;
    { t.refreshRate() } -> std::convertible_to<std::uint32_t>;
};

} // namespace morpheus::gfx::concepts
