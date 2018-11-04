#include <core/gfx/render_target.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

render_target::render_target(
	const std::uint32_t width,
	const std::uint32_t height,
	const std::uint32_t colourDepth
)
:   mWidth(width),
    mHeight(height),
    mColourDepth(colourDepth)
{
}

//---------------------------------------------------------------------------------------------------------------------

render_target::~render_target()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
