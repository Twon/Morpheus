#pragma once

#include <morpheus/core/base/platform.hpp>
#include <string>

namespace morpheus::gfx
{

/*! \class RenderSystem
        A render system provides an abstraction to a platform's graphics hardware.  Such hardware
        is typically accessed via an API which abstracts direct access to the hardware in user
        space within an application.  The render system is the top level abstraction of such an
        API and supports the creation of all graphics primitives needed to access the functionality
        of the hardware.
 */
class RenderSystem {
public:


    /// \name Life cycle
    ///@{
    /*!

     */
    RenderSystem() = default; // LCOV_EXCL_LINE
    ///@}

    /// \name Life cycle
    ///@{
    void beginFrame(){}
    void endFrame(){}
    ///@}

private:
};

} // namespace morpheus::gfx
