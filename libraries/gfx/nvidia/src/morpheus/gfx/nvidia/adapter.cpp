#include <morpheus/gfx/nvidia/adapter.hpp>
#include <morpheus/gfx/nvidia/driver.hpp>
#include <morpheus/gfx/platform/vendor.hpp>
#include <morpheus/core/base/verify.hpp>

#include <windows.h>
#include <array>

namespace morpheus::gfx::nvidia::nvapi
{

concurrency::Generator<Adapter> enumerateAdapters()
{
    Driver driver;

    NvU32 gpuCount = 0;
    std::array<NvPhysicalGpuHandle, NVAPI_MAX_PHYSICAL_GPUS> gpus;
    MORPHEUS_VERIFY(driver.NvAPI_EnumPhysicalGPUs(gpus.data(), &gpuCount) == NVAPI_OK);
    for (std::uint32_t adapters = 0; adapters < gpuCount; ++adapters)
    {
        using NvAPI_ShortString = std::array<char, NVAPI_SHORT_STRING_MAX>;
        NvAPI_ShortString gpuName = {};
        LUID id = {};
        MORPHEUS_VERIFY(driver.NvAPI_GPU_GetFullName(gpus[adapters], gpuName.data()) == NVAPI_OK);
        MORPHEUS_VERIFY(driver.NvAPI_GPU_GetAdapterIdFromPhysicalGpu(gpus[adapters], &id) == NVAPI_OK);

        co_yield Adapter(id.HighPart, gpuName.data(), Vendor::NVidia);
    }
}

} // namespace morpheus::gfx::nvidia::nvapi
