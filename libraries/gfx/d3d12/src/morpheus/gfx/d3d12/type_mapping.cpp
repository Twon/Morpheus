#include "morpheus/gfx/d3d12/type_mapping.hpp"

namespace morpheus::gfx::d3d12
{

//---------------------------------------------------------------------------------------------------------------------

DXGI_FORMAT types::map(
    const pixel_format format
)
{
    switch(format) {
/*    case DXGI_L8:
        return pixel_format::L8;
    case DXGI_L16:
        return pixel_format::L16;
    case DXGI_A8:
        return pixel_format::A8;
    case DXGI_A4L4:
        return pixel_format::A4L4;
    case DXGI_A8L8:
        return pixel_format::A8L8;
    case DXGI_R3G3B2:
        return pixel_format::R3G3B2;
    case DXGI_R5G6B5:
        return pixel_format::R5G6B5;
    case DXGI_A1R5G5B5:
        return pixel_format::A1R5G5B5;
    case DXGI_A4R4G4B4:
        return pixel_format::A4R4G4B4;
    case DXGI_R8G8B8:
        return pixel_format::R8G8B8;
    case DXGI_A8R8G8B8:
        return pixel_format::A8R8G8B8;
    case DXGI_A8B8G8R8:
        return pixel_format::A8B8G8R8;
    case DXGI_X8R8G8B8:
        return pixel_format::X8R8G8B8;
    case DXGI_X8B8G8R8:
        return pixel_format::X8B8G8R8;
    case DXGI_A2R10G10B10:
        return pixel_format::A2R10G10B10;
    case DXGI_A2B10G10R10:
        return pixel_format::A2B10G10R10;*/
    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

//---------------------------------------------------------------------------------------------------------------------

pixel_format types::map(
    const DXGI_FORMAT format
)
{
    switch(format) {
/*    case DXGI_L8:
        return pixel_format::L8;
    case DXGI_L16:
        return pixel_format::L16;
    case DXGI_A8:
        return pixel_format::A8;
    case DXGI_A4L4:
        return pixel_format::A4L4;
    case DXGI_A8L8:
        return pixel_format::A8L8;
    case DXGI_R3G3B2:
        return pixel_format::R3G3B2;
    case DXGI_R5G6B5:
        return pixel_format::R5G6B5;
    case DXGI_A1R5G5B5:
        return pixel_format::A1R5G5B5;
    case DXGI_A4R4G4B4:
        return pixel_format::A4R4G4B4;
    case DXGI_R8G8B8:
        return pixel_format::R8G8B8;
    case DXGI_A8R8G8B8:
        return pixel_format::A8R8G8B8;
    case DXGI_A8B8G8R8:
        return pixel_format::A8B8G8R8;
    case DXGI_X8R8G8B8:
        return pixel_format::X8R8G8B8;
    case DXGI_X8B8G8R8:
        return pixel_format::X8B8G8R8;
    case DXGI_A2R10G10B10:
        return pixel_format::A2R10G10B10;
    case DXGI_A2B10G10R10:
        return pixel_format::A2B10G10R10;*/
    default:
        return pixel_format::UNKNOWN;
    }
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
