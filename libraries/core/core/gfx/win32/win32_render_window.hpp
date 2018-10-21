#pragma once

#include <core/gfx/render_window.hpp>

namespace morpheus::gfx::win32
{

/*! \class render_window
 */
class MORPHEUS_API_EXPORT render_window : public gfx::render_window {
public:
    virtual ~render_window() override;

private:
};

} // namespace morpheus::gfx::win32
