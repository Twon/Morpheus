#include <morpheus/gfx/gl4/wgl/adapter.hpp>
#include <morpheus/gfx/platform/concepts/adapter.hpp>
#include <morpheus/gfx/platform/win32/error.hpp>

#include <catch2/catch_all.hpp>

#include <morpheus/core/conformance/expected.hpp>

#include <algorithm>
#include <vector>

#include <cfgmgr32.h>
#include <windows.h>
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
// #error "Missing define"
#endif

#include <devpkey.h>
#include <setupapi.h>

#include <devpkey.h>
#include <initguid.h>

#include <Cfgmgr32.h>
#include <Wiaintfc.h>

#include <devguid.h>
#include <rpc.h>
#include <winioctl.h>

/*
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#ifdef _WIN32
    #include <windows.h>
// extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000000;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000000;
#endif

namespace morpheus::gfx::gl4::wgl
{

namespace
{
using PathInfoArray = std::vector<DISPLAYCONFIG_PATH_INFO>;
using ModeInfoArray = std::vector<DISPLAYCONFIG_MODE_INFO>;
using DisplayConfig = std::pair<PathInfoArray, ModeInfoArray>;

/// Path mapping an output monitor to the graphic adapter mapped to it.
using Path = std::pair<DISPLAYCONFIG_TARGET_DEVICE_NAME, DISPLAYCONFIG_ADAPTER_NAME>;

auto getDisplayConfigBufferSizes() -> exp_ns::expected<std::pair<UINT32, UINT32>, std::string>
{
    UINT32 pathCount = 0, modeCount = 0;
    auto const result = GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount);
    if (result != ERROR_SUCCESS)
    {
        return exp_ns::unexpected(win32::GetLastErrorString(result));
    }
    return {
        std::pair{pathCount, modeCount}
    };
}

auto queryDisplayConfig(DisplayConfig config) -> exp_ns::expected<DisplayConfig, std::string>
{
    auto& [pathInfo, modeInfo] = config;
    UINT32 pathSize = static_cast<UINT32>(pathInfo.size());
    UINT32 modeSize = static_cast<UINT32>(modeInfo.size());
    ULONG const result = QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathSize, pathInfo.data(), &modeSize, modeInfo.data(), NULL);
    if (result != ERROR_SUCCESS)
        return exp_ns::unexpected(win32::GetLastErrorString(result));
    return config;
}

auto targetDeviceName(DISPLAYCONFIG_PATH_INFO const& path) -> exp_ns::expected<DISPLAYCONFIG_TARGET_DEVICE_NAME, std::string>
{
    DISPLAYCONFIG_TARGET_DEVICE_NAME targetName = {};
    targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    targetName.header.size = sizeof(targetName);
    targetName.header.adapterId = path.targetInfo.adapterId;
    targetName.header.id = path.targetInfo.id;
    auto const result = DisplayConfigGetDeviceInfo(&targetName.header);
    if (result != ERROR_SUCCESS)
    {
        return exp_ns::unexpected(win32::GetLastErrorString(result));
    }
    return targetName;
}

auto adapterName(DISPLAYCONFIG_PATH_INFO const& path) -> exp_ns::expected<DISPLAYCONFIG_ADAPTER_NAME, std::string>
{
    DISPLAYCONFIG_ADAPTER_NAME adapterName = {};
    adapterName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    adapterName.header.size = sizeof(adapterName);
    adapterName.header.adapterId = path.sourceInfo.adapterId;
    adapterName.header.id = 0;
    auto const result = DisplayConfigGetDeviceInfo(&adapterName.header);
    if (result != ERROR_SUCCESS)
    {
        return exp_ns::unexpected(win32::GetLastErrorString(result));
    }
    return adapterName;
}

} // namespace

exp_ns::expected<DisplayConfig, std::string> getCurrentDisplayConfig()
{
    // clang-format off
    return getDisplayConfigBufferSizes()
        .and_then([](auto counts) -> exp_ns::expected<DisplayConfig, std::string>
            {
                return std::apply([](auto&&... args)
                    {
                        return DisplayConfig(std::forward<decltype(args)>(args)...);
                    },
                    std::move(counts)
                );
            })
        .and_then([](auto config)
            { return queryDisplayConfig(std::move(config)); });
    // clang-format on
}

auto getDevicesPaths(DisplayConfig const& config) -> exp_ns::expected<std::vector<Path>, std::string>
{
    auto& [paths, _] = config;

    // clang-format off
    auto r = paths | std::ranges::views::transform([](auto const& path)
        {
            return std::pair{targetDeviceName(path), adapterName(path)};
        });

    auto const result = std::ranges::fold_left(std::move(r), exp_ns::expected<std::vector<Path>, std::string>{},
        [](auto&& result, auto element) -> exp_ns::expected<std::vector<Path>, std::string>
        {
            if (!result) {
                return exp_ns::unexpected(result.error());
            }

            if (!element.first) {
                return exp_ns::unexpected(element.first.error());
            }

            if (!element.second) {
                return exp_ns::unexpected(element.second.error());
            }

            result.value().push_back(Path{std::move(element).first.value(), std::move(element).second.value()});
            return std::move(result);
        });
    // clang-format on

    return result;
}

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
    //    DISPLAYCONFIG_ADAPTER_NAME adapter{ {DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME , sizeof(DISPLAYCONFIG_ADAPTER_NAME)} };
    //    MORPHEUS_VERIFY(DisplayConfigGetDeviceInfo(adapter.header) == ERROR_SUCCESS);

    LUID targetAdapter; // the LUID of the target we want to find the source for
    ULONG targetId = 0; // the id of the target we want to find the source for

    DISPLAYCONFIG_ADAPTER_NAME adapterName = {};
    adapterName.header.adapterId = LUID{68511, 0}; // path.targetInfo.adapterId;
    adapterName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    adapterName.header.size = sizeof(adapterName);
    auto result2 = DisplayConfigGetDeviceInfo(&adapterName.header);

    DISPLAYCONFIG_ADAPTER_NAME adapterName2 = {};
    adapterName2.header.adapterId = LUID{69333, 0}; // path.targetInfo.adapterId;
    adapterName2.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    adapterName2.header.size = sizeof(adapterName2);
    auto result3 = DisplayConfigGetDeviceInfo(&adapterName2.header);

    DEVPROPTYPE PropertyType = DEVPROP_TYPE_EMPTY;
    ULONG PropertySize = 0;
    ULONG SomeValue = 0;

    SP_DEVICE_INTERFACE_DATA interfaceData = {0};
    interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    //    HDEVINFO deviceInfoSet = SetupDiCreateDeviceInfoList(NULL, NULL);
    //    SetupDiOpenDeviceInterface(deviceInfoSet, adapterName.adapterDevicePath, 0, &interfaceData);
    /*
    PropertySize = sizeof(SomeValue);
    auto cr = CM_Get_DevNode_PropertyW(DevInst,
        &DEVPKEY_Device_InstanceId,
        &PropertyType,
        (PBYTE)&SomeValue,
        &PropertySize,
        0);
*/
    DISPLAYCONFIG_PATH_SOURCE_INFO* pSource = NULL; // will contain the answer

    auto result = getCurrentDisplayConfig().and_then([](DisplayConfig const& config) { return getDevicesPaths(config); });

    auto result4 = getCurrentDisplayConfig();
    REQUIRE(result4);

    auto& [pathInfo, modeInfo] = result4.value();

    for (UINT32 tryEnable = 0;; ++tryEnable)
    {
        DISPLAYCONFIG_PATH_INFO* pCurrentPath = NULL;
        for (UINT32 i = 0, j = 0; i < pathInfo.size(); ++i)
        {
            if (pathInfo[i].targetInfo.targetAvailable && !memcmp(&pathInfo[i].targetInfo.adapterId, &targetAdapter, sizeof(LUID)) &&
                pathInfo[i].targetInfo.id == targetId)
            {
                pathInfo[i].targetInfo.statusFlags |= DISPLAYCONFIG_TARGET_IN_USE;

                if (j++ == tryEnable)
                {
                    pCurrentPath = &pathInfo[i];

                    if (pCurrentPath->flags & DISPLAYCONFIG_PATH_ACTIVE)
                    {
                        // trivial early out... user already had this enabled, therefore we know this is the right source.
                        pSource = &pCurrentPath->sourceInfo;
                        break;
                    }

                    // try to activate this particular source
                    pCurrentPath->flags |= DISPLAYCONFIG_PATH_ACTIVE;
                    pCurrentPath->sourceInfo.statusFlags |= DISPLAYCONFIG_SOURCE_IN_USE;
                }
            }
        }

        if (!pCurrentPath)
            return; // failure. tried everything, apparently no source is connected to our target

        LONG rc = SetDisplayConfig(
            pathInfo.size(), pathInfo.data(), modeInfo.size(), modeInfo.data(), SDC_VALIDATE | SDC_USE_SUPPLIED_DISPLAY_CONFIG | SDC_ALLOW_CHANGES);

        if (rc != ERROR_SUCCESS)
        {
            // it didn't work, undo trying to activate this source
            pCurrentPath->flags &= ~DISPLAYCONFIG_PATH_ACTIVE;
            pCurrentPath->sourceInfo.statusFlags &= DISPLAYCONFIG_SOURCE_IN_USE;
        }
        else
        {
            pSource = &pCurrentPath->sourceInfo;
            break; // success!
        }
    }
    // Note: pSource is pointing to the source relevant to the relevant source now!
    // You just need to copy off whatever you need.
}

TEST_CASE("Concept checks for WGL adapters", "[morpheus.gfx.gl.wgl.adapter.concepts]")
{
    //    STATIC_REQUIRE(concepts::VideoMode<VideoMode>);
    // STATIC_REQUIRE(requires(Adapter t) { { t.getName() } -> std::convertible_to<std::string_view>; });
    // STATIC_REQUIRE(requires(Adapter t) { { t.getVideoModes() } -> morpheus::gfx::concepts::VideoModeRange; });

    //    STATIC_REQUIRE(gfx::concepts::Adapter<Adapter>);
}

TEST_CASE("Iterates over the adapters in the list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
    GIVEN("An adapter list")
    {
        // adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
            for (auto& adapter : enumerateAdapters())
            {
                INFO("The adapter id is: " << adapter.id());
            }
        }
    }
}

/*
TEST_CASE("Iterates over the adapters in the list via openCL", "[morpheus.core.gfx.adapter_list.cl]")
{

    // Host/device data structures
    cl_platform_id platform;
    std::vector<cl_device_id> devices;
    cl_uint num_devices, addr_data;
    cl_int i, err;

    // Extension data
    char name_data[256], ext_data[4096];

    // Identify a platform
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err < 0) {
        perror("Couldn't find any platforms");
        exit(1);
    }

    // Determine number of connected devices
    err = clGetDeviceIDs(platform,
        // CL_DEVICE_TYPE_GPU,
        CL_DEVICE_TYPE_ALL,      // jyl -- query for all available opencl devices
        1,
        NULL,
        &num_devices);

    if (err < 0) {
        perror("Couldn't find any devices");
        exit(1);
    }

    // Access connected devices
    devices.resize(num_devices);

    clGetDeviceIDs(platform,
        // CL_DEVICE_TYPE_GPU,
        CL_DEVICE_TYPE_ALL,          // jyl -- query for all available opencl devices
        num_devices,
        devices.data(),
        NULL);

    // Obtain data for each connected device
    for (i = 0; i < num_devices; i++) {

        err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME,
            sizeof(name_data), name_data, NULL);
        if (err < 0) {
            perror("\nERROR! Couldn't read extension data");
            exit(1);
        }
        clGetDeviceInfo(devices[i], CL_DEVICE_ADDRESS_BITS,
            sizeof(ext_data), &addr_data, NULL);

        clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS,
            sizeof(ext_data), ext_data, NULL);

        printf("\n\nNAME: %s\nADDRESS_WIDTH: %u\nEXTENSIONS: %s",
            name_data, addr_data, ext_data);
    }
}*/

} // namespace morpheus::gfx::gl4::wgl
