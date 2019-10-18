#include <core/gfx/adapters/adapter.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

adapter::adapter(
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

} // namespace morpheus::gfx
