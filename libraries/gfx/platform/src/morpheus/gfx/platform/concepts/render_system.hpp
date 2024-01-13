#pragma once

#include "morpheus/core/meta/concepts/copyable.hpp"
#include "morpheus/gfx/concepts/adapter.hpp"

namespace morpheus::gfx::concepts
{

template <typename T>
concept RenderSystem = requires(T t)
{
    requires !meta::Copyable<T>;
    { t.adapters() } -> AdapterRange;
};

} // namespace morpheus::gfx::concepts
