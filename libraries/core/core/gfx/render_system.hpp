#pragma once

#include <core/platform.hpp>
#include <string>

namespace morpheus::gfx
{

/*! \class render_system
        A render system provides an abstraction to a platform's graphics hardware.  Such hardware
        is typically accessed via an API which abstracts direct access to the hardare in user
        space within an application.  The render system is the top level abstraction of such an
        API and supports the creation of all graphics primitives needed to access the functionality
        of the hardware.
 */
class MORPHEUSCORE_EXPORT render_system {
public:
    virtual ~render_system() = 0;

private:
};

} // namespace morpheus::gfx
