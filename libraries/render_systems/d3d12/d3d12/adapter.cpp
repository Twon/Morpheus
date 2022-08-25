#include <core/conformance/format.hpp>
#include <d3d12/adapter_list.hpp>
#include <d3d12/adapter.hpp>

#include <exception>
#include <utility>

namespace morpheus::gfx::d3d12
{

namespace
{

/// \using DXGIFactory
///     A RAII wrapper for the IDXGIFactory4 interface.
using DXGIFactory = Microsoft::WRL::ComPtr<IDXGIFactory4>;

/// \using DXGIOutput
///     A RAII wrapper for the IDXGIOutput interface.
using DXGIOutput = Microsoft::WRL::ComPtr<IDXGIOutput>;

auto createDXGIFactory()
{
    DXGIFactory dxgiFactory;
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory))))
    {
        throw std::runtime_error(fmt_ns::format("Unable to create DXGI Factory", "panic"));
    }
    return dxgiFactory;
}

auto getAdapterDescription(const DXGIAdapter& adapter)
{
    DXGI_ADAPTER_DESC1 desc{};
    adapter->GetDesc1(&desc);
    return desc;
}

auto getOutputModes(const DXGIOutput& output)
{
	UINT numModes = 0;
	auto hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr);
    if (FAILED(hr)) {

    }

    std::vector<DXGI_MODE_DESC> displayModes(numModes);
	hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModes.data());
    if (FAILED(hr)) {

    }

    return displayModes;
}

auto getOutputModes(const DXGIAdapter& adapter)
{
    DXGIOutput output;
    std::vector<DXGI_MODE_DESC> displayModes;

    for (UINT outputCount = 0; DXGI_ERROR_NOT_FOUND != adapter->EnumOutputs(outputCount, &output); ++outputCount)
    {
        auto outputDisplayModes = getOutputModes(output);
        displayModes.insert(
            displayModes.end(),
            std::make_move_iterator(outputDisplayModes.begin()),
            std::make_move_iterator(outputDisplayModes.end())
        );
            
    }

    return displayModes;
}

}

Adapter::Adapter(
    DXGIAdapter dxgiAdapter
)
:   mDxgiAdapter(std::move(dxgiAdapter)),
    mDescription(getAdapterDescription(mDxgiAdapter))
{
}

concurrency::Generator<Adapter> enumerateAdapters() 
{
    auto const dxgiFactory = createDXGIFactory();
    DXGIAdapter pDXGIAdapter;
    for (UINT adapterId = 0; DXGI_ERROR_NOT_FOUND != dxgiFactory->EnumAdapters1(adapterId, &pDXGIAdapter); ++adapterId)
    {
        //            // Ignore software adapters
        //            if (graphics_adapter.dxgi_description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        //                continue;
        //            }
        co_yield Adapter(pDXGIAdapter);
    }
}

} // namespace morpheus::gfx::d3d12
