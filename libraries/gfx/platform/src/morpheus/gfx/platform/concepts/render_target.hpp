#pragma once

#include "core/gfx/concepts/video_mode.hpp"

namespace morpheus::gfx::concepts
{

template <typename T>
concept RenderTarget = requires(T t) {
    { t.refreshRate() } -> std::convertible_to<std::uint32_t>;
};

} // namespace morpheus::gfx::concepts
