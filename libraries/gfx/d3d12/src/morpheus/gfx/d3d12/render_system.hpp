#pragma once

#include <morpheus/gfx/platform/render_system.hpp>
#include <wrl.h>

namespace morpheus::gfx::d3d12
{

/*! \class Rrender_system
        Rendering system abstraction based upon the Microsoft DirectX 12 API.
 */
class RenderSystem : public gfx::RenderSystem
{
public:
    RenderSystem();

private:
};

} // namespace morpheus::gfx::d3d12
