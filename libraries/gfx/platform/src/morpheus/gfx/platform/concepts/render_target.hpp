#pragma once

#include "core/gfx/concepts/video_mode.hpp"

namespace morpheus::gfx::concepts
{

template <typename T>
concept RenderTarget = requires(T t)
{

};

} // namespace morpheus::gfx::concepts
