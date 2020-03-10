#pragma once

#import <core/gfx/render_system.hpp>

namespace morpheus::gfx::metal
{

/*! \class render_system
        Rendering system abstraction based upon the Metal graphics API.
 */
class render_system : gfx::render_system {
public:
    virtual ~render_system();

private:
};

} // namespace morpheus::gfx::metal
