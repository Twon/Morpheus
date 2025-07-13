#include "morpheus/gfx/d3d12/adapter.hpp"
#include "morpheus/gfx/d3d12/render_system.hpp"
#include "morpheus/gfx/d3d12/types.hpp"

#include <d3d12.h>

#include <wrl/client.h>


namespace morpheus::gfx::d3d12
{

template <typename T>
DXGIExpected<T> toDXGIExpected(HRESULT hr, T&& val)
{
    if (SUCCEEDED(hr)) {
        return std::forward<T>(val);
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

RenderSystem::RenderSystem()
{
    //createDGXIFactory().and_then(
}

} // namespace morpheus::gfx::d3d12
