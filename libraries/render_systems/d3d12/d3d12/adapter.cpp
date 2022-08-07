#include <d3d12/adapter.hpp>
#include <utility>

namespace morpheus::gfx::d3d12
{

namespace
{
    /*! \using DXGIOutput
            A RAII wrapper for the IDXGIOutput interface.
     */
    using DXGIOutput = Microsoft::WRL::ComPtr<IDXGIOutput>;


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
//---------------------------------------------------------------------------------------------------------------------

adapter::adapter(
    DXGIAdapter dxgiAdapter
)
:   mDxgiAdapter(std::move(dxgiAdapter)),
    mDescription(getAdapterDescription(mDxgiAdapter))
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::d3d12
