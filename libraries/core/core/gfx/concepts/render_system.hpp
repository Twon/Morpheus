#pragma once

#include "core/gfx/concepts/adapter.hpp"

namespace morpheus::gfx::concepts
{

template <typename T>
concept RenderSystem = requires(T t)
{
    { t.adapters() } -> AdapterRange;
};

} // namespace morpheus::gfx::concepts
