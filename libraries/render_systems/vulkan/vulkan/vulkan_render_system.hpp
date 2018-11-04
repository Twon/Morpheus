#pragma once

#include <core/gfx/render_system.hpp>

namespace morpheus::gfx::vulkan
{

/*! \class render_system
        Rendering system abstraction based upon the Vulkan graphics API.
 */
class render_system {
public:
    virtual ~render_system();

private:
};

} // namespace morpheus::gfx::vulkan
