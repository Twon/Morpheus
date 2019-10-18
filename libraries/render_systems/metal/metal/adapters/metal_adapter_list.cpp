#include <core/gfx/adapters/adapter_list.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

adapter_list::adapter_list(
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
