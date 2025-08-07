#include "morpheus/gfx/d3d12/adapter.hpp"
#include "morpheus/gfx/d3d12/render_system.hpp"


#include <d3d12.h>

#include <wrl/client.h>

#include <utility>

namespace morpheus::gfx::d3d12
{

template <typename T>
DXGIExpected<T> toDXGIExpected(HRESULT hr, T&& val)
{
    if (SUCCEEDED(hr)) {
        return std::move(val);
    }
    else {
        return exp_ns::unexpected(hr);
    }
}

DXGIExpected<DXGIFactory> createDGXIFactory()
{
    DXGIFactory factory;
    HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&factory));
    return toDXGIExpected(hr, std::move(factory));
}


DXGIExpected<D3D12Device> createDevice(Adapter const& adapter)
{
    D3D12Device device;
    HRESULT hr = D3D12CreateDevice(adapter.dxgiAdapter().Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
    return toDXGIExpected(hr, std::move(device));
}

auto RenderSystem::create(Adapter const& adapter) -> exp_ns::expected<RenderSystem, std::string>
{
    //auto device = createDevice(adapter).and_then([](auto&& /*device*/)
    //    {
    //        return exp_ns::expected<RenderSystem, std::string>{RenderSystem{}};
    //    }
    //);
    //return device;
    return exp_ns::expected<RenderSystem, std::string>{RenderSystem{}};
}

} // namespace morpheus::gfx::d3d12
