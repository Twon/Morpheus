#pragma once

#include <core/platform.hpp>
#include <core/gfx/render_target.hpp>
#include <string>

namespace morpheus::gfx
{

/*! \class render_window
 */
class MORPHEUSCORE_EXPORT render_window : public render_target  {
public:
    virtual ~render_window() override;

private:

};

} // namespace morpheus::gfx
