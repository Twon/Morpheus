#pragma once
#include <morpheus/core/base/platform.hpp>
#include <morpheus/gfx/gl4/platform.hpp>
#include <morpheus/gfx/platform/concepts/render_window.hpp>

namespace morpheus::gfx::gl4
{

/// \class Traits
///     Traits class describing the traits of a GL render system.
/// \tparam W
///     The type of rendering window.
template <concepts::RenderWindow W>
struct Traits
{
    using Window = W;
};

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

using GL4Traits = Traits<platform::Window>;

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

struct GL4Traits
{
    using Window = int;
};

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)

struct GL4Traits
{
    using Window = int;
};

#endif

} // namespace morpheus::gfx::gl4
