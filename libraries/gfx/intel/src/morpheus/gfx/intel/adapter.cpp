#include <morpheus/gfx/platform/vendor.hpp>
#include <morpheus/gfx/intel/adapter.hpp>
#include <morpheus/core/base/verify.hpp>

#include <igcl_api.h>
#include <Windows.h>
#include <vector>

namespace morpheus::gfx::intel::win32
{

concurrency::Generator<Adapter> enumerateAdapters()
{
    ctl_init_args_t ctlInitArgs{ 
        .Size = sizeof(ctl_init_args_t),
        .Version = 0, 
        .AppVersion = CTL_MAKE_VERSION(CTL_IMPL_MAJOR_VERSION, CTL_IMPL_MINOR_VERSION),
        .flags = CTL_INIT_FLAG_USE_LEVEL_ZERO
    };
    ZeroMemory(&ctlInitArgs.ApplicationUID, sizeof(ctl_application_id_t));
    ctl_api_handle_t hAPIHandle = nullptr;

    std::uint32_t adapterCount = 0;
    MORPHEUS_VERIFY(ctlInit(&ctlInitArgs, &hAPIHandle) == CTL_RESULT_SUCCESS);
    MORPHEUS_VERIFY(ctlEnumerateDevices(hAPIHandle, &adapterCount, nullptr) == CTL_RESULT_SUCCESS);

    std::vector<ctl_device_adapter_handle_t> devices(adapterCount);
    MORPHEUS_VERIFY(ctlEnumerateDevices(hAPIHandle, &adapterCount, devices.data()) == CTL_RESULT_SUCCESS);

    for (auto const& device : devices)
    {
        LUID adapterID{};
        ctl_device_adapter_properties_t properties{
            .Size=sizeof(properties), 
            .Version=0, 
            .pDeviceID=&adapterID, 
            .device_id_size = sizeof(LUID)
        };
        MORPHEUS_VERIFY(ctlGetDeviceProperties(device, &properties) == CTL_RESULT_SUCCESS);
        co_yield Adapter(
            adapterID.LowPart,
            properties.name,
            *vendorFromPciId(properties.pci_vendor_id)
        );
    }
}

} // namespace morpheus::gfx::intel::win32
