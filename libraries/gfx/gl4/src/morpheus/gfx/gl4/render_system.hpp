#pragma once

//#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/platform/render_system.hpp>

namespace morpheus::gfx::gl4
{

/// \class RenderSystem
///     Rendering system abstraction based upon the OpenGL 4 graphics API.
/// \tparam T
///     The traits of the rendering system.
template <class T>
class RenderSystem : public gfx::RenderSystem
{
public:
    using Window = typename T::Window;

private:
};

} // namespace morpheus::gfx::gl4
