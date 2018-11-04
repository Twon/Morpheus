#pragma once

#include <core/platform.hpp>
#include <core/gfx/render_target.hpp>
#include <string>

namespace morpheus::gfx
{

/*! \class render_window
        A render window is a specialisation of a render target within the native windowing system
        of the target platform.
 */
class MORPHEUSCORE_EXPORT render_window : public render_target  {
public:
   /// \name Life cycle
	///@{
	/*! Constructs a render target with the specified parameters.
	    \param[in] width
             The width in pixels of the render target.
	    \param[in] height
             The height in pixels of the render target.
	    \param[in] colourDepth
             The colour depth of the pixels of the render target.
	    \param[in] startX
             The starting X position in pixels of the render window.
	    \param[in] startY
             The starting Y position in pixels of the render window.
	    \param[in] windowName
             The name of the window.
	 */
	render_window(
		const std::uint32_t width,
		const std::uint32_t height,
		const std::uint32_t colourDepth,
		const std::uint32_t startX,
		const std::uint32_t startY,
		const std::string windowName
	);

    //! Destructor
    virtual ~render_window() override;
    ///@}

private:
    const std::uint32_t mStartX;
    const std::uint32_t mStartY;
    const std::string mWindowName;
};

} // namespace morpheus::gfx
