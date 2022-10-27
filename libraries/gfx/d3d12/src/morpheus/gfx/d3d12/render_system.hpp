#pragma once

#include <morpheus/gfx/platform/render_system.hpp>
#include <wrl.h>

namespace morpheus::gfx::d3d12
{

/*! \class render_system
        Rendering system abstraction based upon the Microsoft DirectX 12 API.
 */
class render_system : public gfx::render_system {
public:
    virtual ~render_system();

private:
};

} // namespace morpheus::gfx::d3d12
