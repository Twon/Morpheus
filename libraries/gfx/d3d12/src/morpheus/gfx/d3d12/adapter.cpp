#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/gfx/d3d12/adapter.hpp"
#include "morpheus/gfx/d3d12/exceptions.hpp"
#include "morpheus/gfx/d3d12/types.hpp"
#include "morpheus/gfx/d3d12/verify.hpp"

#include <d3d12.h>

#include <wrl/client.h>

#include <exception>
#include <utility>

namespace morpheus::gfx::d3d12
{

template <typename T>
void throwOnError(DXGIExpected<T> const& e)
{
    if (!e) {
        throwD3D12Exception("HRESULT: 0x{:08X} - ", static_cast<uint32_t>(e.error()), getLastErrorMessage());
    }
}

/// \param[in] e The expected type from which to throw the unexpected state or return the valid value.
/// \tparam T The expected type in the DXGIExpected.
/// \return The expect value type if not in an error state.
 template <typename T>
T throwOrUnwrap(DXGIExpected<T>&& e)
{
    throwOnError(e);
    return std::move(*e);
}



namespace
{

auto createDXGIFactory() -> DXGIExpected<DXGIFactory>
{
    DXGIFactory dxgiFactory;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    if (FAILED(hr))
        return exp_ns::unexpected(hr);
    return dxgiFactory;
}

auto getAdapterDescription(const DXGIAdapter& adapter) -> DXGIExpected<DXGI_ADAPTER_DESC1>
{
    DXGI_ADAPTER_DESC1 desc{};
    HRESULT hr = adapter->GetDesc1(&desc);
    if (FAILED(hr))
        return exp_ns::unexpected(hr);
    return desc;
}

auto getOutputModes(const DXGIOutput& output) -> DXGIExpected<std::vector<DXGI_MODE_DESC>>
{
    UINT numModes = 0;
    HRESULT hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr);
    if (FAILED(hr))
        return std::unexpected(hr);

    std::vector<DXGI_MODE_DESC> displayModes(numModes);
    hr = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModes.data());
    if (FAILED(hr))
        return std::unexpected(hr);
    return displayModes;
}

auto getOutputModes(const DXGIAdapter& adapter)
{
    DXGIOutput output;
    std::vector<DXGI_MODE_DESC> displayModes;

    for (UINT outputCount = 0; DXGI_ERROR_NOT_FOUND != adapter->EnumOutputs(outputCount, &output); ++outputCount)
    {
        auto outputDisplayModes = throwOrUnwrap(getOutputModes(output));
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
:   mDxgiAdapter(std::move(dxgiAdapter))
,   mDescription(throwOrUnwrap(getAdapterDescription(mDxgiAdapter)))
{
}

[[nodiscard]] Vendor Adapter::vendor() const noexcept
{
    auto const vendor = vendorFromPciId(mDescription.VendorId);
    MORPHEUS_ASSERT(vendor);
    return *vendor;
}

concurrency::Generator<Adapter> enumerateAdapters()
{
    auto const dxgiFactory = throwOrUnwrap(createDXGIFactory());

    DXGIAdapter pDXGIAdapter;
    for (UINT adapterId = 0; ; ++adapterId)
    {
        if (DXGI_ERROR_NOT_FOUND != dxgiFactory->EnumAdapters1(adapterId, &pDXGIAdapter)) {
            break;
        }

        // See if the adapter support the minimum level required by Direct 3D 12
        if (FAILED(D3D12CreateDevice(pDXGIAdapter.Get(), D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr))) {
            continue;
        }

        co_yield Adapter(pDXGIAdapter);
    }
}

} // namespace morpheus::gfx::d3d12
