#include <morpheus/gfx/d3d12/video_mode_list.hpp>

namespace morpheus::gfx::d3d12
{

namespace
{
    auto createAdapters(std::vector<DXGI_MODE_DESC> const& /*displayModes*/)
    {
        return 0;
    }
}

//---------------------------------------------------------------------------------------------------------------------

video_mode_list::video_mode_list(std::vector<DXGI_MODE_DESC> const& /*displayModes*/)
//:   mWidth(width),
//    mHeight(height),
//    mColourDepth(colourDepth)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
