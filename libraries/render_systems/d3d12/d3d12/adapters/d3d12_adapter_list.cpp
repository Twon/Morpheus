#include <d3d12/adapters/d3d12_adapter_list.hpp>
#include <d3d12/adapters/d3d12_adapter.hpp>
//#include <fmt/core.h>

namespace morpheus::gfx::d3d12
{


namespace
{
    auto createDXGIFactory()
    {   
        DXGIFactory dxgiFactory;
        if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory))))
        {
//            throw std::runtime_error(fmt::format("Unable to create DXGI Factory", "panic"));
        }
        return dxgiFactory;
    }

    auto createAdapters(const DXGIFactory& dxgiFactory)
    {
        DXGIAdapter pDXGIAdapter;
        std::vector<adapter> adapters;
        for (UINT adapterId = 0; DXGI_ERROR_NOT_FOUND != dxgiFactory->EnumAdapters1(adapterId, &pDXGIAdapter); ++adapterId)
        {
            adapter graphics_adapter(pDXGIAdapter);
//            // Ignore software adapters
//            if (graphics_adapter.dxgi_description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
//                continue;
//            }
            adapters.push_back(std::move(graphics_adapter));
        }
        return adapters;
    }
}

//---------------------------------------------------------------------------------------------------------------------

adapter_list::adapter_list()
:   gfx::adapter_list(gfx::adapter_list::adapter_container()),
    mDxgiFactory(createDXGIFactory())
{
    createAdapters(mDxgiFactory);
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
