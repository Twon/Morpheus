#include <gl4/wgl/adapter.hpp>
#include <catch2/catch_all.hpp>

#include <boost/dll/shared_library.hpp>
#include <boost/dll/import.hpp>   
#include <boost/function.hpp>
#include <array>

/*
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#ifdef _WIN32
#include <windows.h>
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#endif

namespace morpheus::test
{
using namespace morpheus::gfx::gl4::wgl;

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
}

TEST_CASE("Iterates over the adapters in the list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
    GIVEN("An adapter list")
    {
        //adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
            for (auto& adapter : enumerateAdapters())
            {
                INFO("The adapter id is: " << adapter.getId());
            }
        }
    }
}


TEST_CASE("Query NVidia graphic adapters", "[morpheus.core.gfx.adapter_list]")
{
    boost::dll::shared_library nvapi("nvapi64.dll", boost::dll::load_mode::search_system_folders);

    using NvAPI_QueryInterface_t = void* (__cdecl)(unsigned int offset);
    using NvAPI_Initialize_t = std::int32_t (__cdecl*)();
    using NvAPI_Unload_t = std::int32_t (__cdecl*)();
    using NvAPI_Unload_t = std::int32_t(__cdecl*)();
 
    constexpr std::size_t NVAPI_MAX_PHYSICAL_GPUS = 64;
    using NvAPI_EnumPhysicalGPUs_t = std::int32_t (__cdecl*)(void* nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS], std::uint32_t* pGpuCount);
    using NvAPI_GPU_GetFullName_t = std::int32_t(__cdecl*)(void* nvGPUHandle, char * const pGpuName);

    constexpr std::uint32_t offset_NvAPI_Initialize = 0x0150E828UL;
    constexpr std::uint32_t offset_NvAPI_Unload = 0xD22BDD7EUL;
    constexpr std::uint32_t offset_NvAPI_EnumPhysicalGPUs = 0xE5AC921FUL;
    constexpr std::uint32_t offset_NvAPI_GPU_GetFullName = 0xCEEE8E9FUL;
    
 /*   auto hNvapi = LoadLibrary("nvapi64.dll");
    void* address = GetProcAddress(hNvapi, "nvapi_QueryInterface");
    auto const NvAPI_QueryInterface = reinterpret_cast<NvAPI_QueryInterface_t>(address);
    auto const NvAPI_InitializeRaw = reinterpret_cast<NvAPI_Initialize_t>(NvAPI_QueryInterface(offset_NvAPI_Initialize));*/

    //static_assert(!boost::is_object<NvAPI_QueryInterface_t>::value);

    static_assert(!boost::is_object<NvAPI_QueryInterface_t>::value);

//    using NvAPI_QueryInterface_t =  void* (__cdecl *)(std::uint32_t offset);
//    auto const& nvapi_QueryInterface = boost::dll::import_alias<NvAPI_QueryInterface_t>("nvapi64.dll", "nvapi_QueryInterface", boost::dll::load_mode::search_system_folders);
    auto const nvapi_QueryInterface = nvapi.get<NvAPI_QueryInterface_t>("nvapi_QueryInterface");
//    REQUIRE(nvapi_QueryInterface);

    auto const NvAPI_Initialize = reinterpret_cast<NvAPI_Initialize_t>(nvapi_QueryInterface(offset_NvAPI_Initialize));
    REQUIRE(NvAPI_Initialize);
    REQUIRE(!NvAPI_Initialize());

    auto const NvAPI_EnumPhysicalGPUs = reinterpret_cast<NvAPI_EnumPhysicalGPUs_t>(nvapi_QueryInterface(offset_NvAPI_EnumPhysicalGPUs));
    REQUIRE(NvAPI_EnumPhysicalGPUs);
    std::uint32_t gpuCount = 0;
    std::array<void*, NVAPI_MAX_PHYSICAL_GPUS> gpus;
    REQUIRE(!NvAPI_EnumPhysicalGPUs(gpus.data(), &gpuCount));

    
    auto const NvAPI_GPU_GetFullName = reinterpret_cast<NvAPI_GPU_GetFullName_t>(nvapi_QueryInterface(offset_NvAPI_GPU_GetFullName));
    REQUIRE(NvAPI_GPU_GetFullName);
    constexpr std::size_t NVAPI_SHORT_STRING_MAX = 64;
    using NvAPI_ShortString = std::array<char, NVAPI_SHORT_STRING_MAX>;
    NvAPI_ShortString gpuName;
    REQUIRE(!NvAPI_GPU_GetFullName(gpus[0], gpuName.data()));

    auto const NvAPI_Unload = reinterpret_cast<NvAPI_Initialize_t>(nvapi_QueryInterface(offset_NvAPI_Unload));
    REQUIRE(NvAPI_Unload);
    REQUIRE(!NvAPI_Unload());
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

} // namespace morpheus::test
