#include "morpheus/gfx/d3d12/type_mapping.hpp"

namespace morpheus::gfx::d3d12
{

//---------------------------------------------------------------------------------------------------------------------

DXGI_FORMAT types::map(PixelFormat const format)
{
    switch (format)
    {
        /*    case DXGI_L8:
                return PixelFormat::L8;
            case DXGI_L16:
                return PixelFormat::L16;
            case DXGI_A8:
                return PixelFormat::A8;
            case DXGI_A4L4:
                return PixelFormat::A4L4;
            case DXGI_A8L8:
                return PixelFormat::A8L8;
            case DXGI_R3G3B2:
                return PixelFormat::R3G3B2;
            case DXGI_R5G6B5:
                return PixelFormat::R5G6B5;
            case DXGI_A1R5G5B5:
                return PixelFormat::A1R5G5B5;
            case DXGI_A4R4G4B4:
                return PixelFormat::A4R4G4B4;
            case DXGI_R8G8B8:
                return PixelFormat::R8G8B8;
            case DXGI_A8R8G8B8:
                return PixelFormat::A8R8G8B8;
            case DXGI_A8B8G8R8:
                return PixelFormat::A8B8G8R8;
            case DXGI_X8R8G8B8:
                return PixelFormat::X8R8G8B8;
            case DXGI_X8B8G8R8:
                return PixelFormat::X8B8G8R8;
            case DXGI_A2R10G10B10:
                return PixelFormat::A2R10G10B10;
            case DXGI_A2B10G10R10:
                return PixelFormat::A2B10G10R10;*/
    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

//---------------------------------------------------------------------------------------------------------------------

PixelFormat types::map(DXGI_FORMAT const format)
{
    switch (format)
    {
        /*    case DXGI_L8:
                return PixelFormat::L8;
            case DXGI_L16:
                return PixelFormat::L16;
            case DXGI_A8:
                return PixelFormat::A8;
            case DXGI_A4L4:
                return PixelFormat::A4L4;
            case DXGI_A8L8:
                return PixelFormat::A8L8;
            case DXGI_R3G3B2:
                return PixelFormat::R3G3B2;
            case DXGI_R5G6B5:
                return PixelFormat::R5G6B5;
            case DXGI_A1R5G5B5:
                return PixelFormat::A1R5G5B5;
            case DXGI_A4R4G4B4:
                return PixelFormat::A4R4G4B4;
            case DXGI_R8G8B8:
                return PixelFormat::R8G8B8;
            case DXGI_A8R8G8B8:
                return PixelFormat::A8R8G8B8;
            case DXGI_A8B8G8R8:
                return PixelFormat::A8B8G8R8;
            case DXGI_X8R8G8B8:
                return PixelFormat::X8R8G8B8;
            case DXGI_X8B8G8R8:
                return PixelFormat::X8B8G8R8;
            case DXGI_A2R10G10B10:
                return PixelFormat::A2R10G10B10;
            case DXGI_A2B10G10R10:
                return PixelFormat::A2B10G10R10;*/
    default:
        return PixelFormat::UNKNOWN;
    }
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
