#pragma once

#include <core/gfx/render_system.hpp>

namespace morpheus::gfx::gl4
{

/*! \class render_system
        Rendering system abstraction based upon the OpenGL 4 graphics API.
 */
class render_system : public gfx::render_system {
public:
    virtual ~render_system() override;

private:
};

} // namespace morpheus::gfx::gl4
