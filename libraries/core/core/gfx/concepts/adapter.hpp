#pragma once

#include "core/gfx/concepts/video_mode.hpp"
#include <string_view>
#include <type_traits>

namespace morpheus::gfx::concepts
{

/// \concept Adapter
///     Adapters define the underlying graphics API abstraction of the underlying graphic hardware device. 
template <typename T>
concept Adapter = requires(T t)
{
    { t.getDescription() } -> std::same_as<std::string_view>;
    { t.getVideoModes() } -> VideoModeContainer;
};

template <typename T>
concept AdapterRange = requires(T t)
{
};

} // namespace morpheus::gfx::concepts
