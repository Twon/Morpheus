#include <d3d12/video_mode_list.hpp>

namespace morpheus::gfx::d3d12
{

namespace
{
    auto createAdapters(const std::vector<DXGI_MODE_DESC>& displayModes)
    {
        return 0;
    }
}

//---------------------------------------------------------------------------------------------------------------------

video_mode_list::video_mode_list(
    const std::vector<DXGI_MODE_DESC>& displayModes
)
//:   mWidth(width),
//    mHeight(height),
//    mColourDepth(colourDepth)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
