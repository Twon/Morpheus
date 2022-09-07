#include <morpheus/gfx/nvidia/driver.hpp>
#include <catch2/catch_all.hpp>

#include <array>

namespace morpheus::gfx::nvidia
{

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.gl.wgl.adapter_list]")
{
}

TEST_CASE("Concept checks for NVidia adapters", "[morpheus.gfx.gl.wgl.adapter.concepts]")
{
    //    STATIC_REQUIRE(concepts::VideoMode<VideoMode>);
        //STATIC_REQUIRE(requires(Adapter t) { { t.getName() } -> std::convertible_to<std::string_view>; });
        //STATIC_REQUIRE(requires(Adapter t) { { t.getVideoModes() } -> morpheus::gfx::concepts::VideoModeRange; });

    //    STATIC_REQUIRE(gfx::concepts::Adapter<Adapter>);
}


TEST_CASE("Query NVidia graphic adapters", "[morpheus.core.gfx.adapter_list]")
{
    boost::dll::shared_library nvapi("nvapi64.dll", boost::dll::load_mode::search_system_folders);

    using NvAPI_QueryInterface_t = void* (__cdecl)(unsigned int offset);
    using NvAPI_Initialize_t = std::int32_t(__cdecl*)();
    using NvAPI_Unload_t = std::int32_t(__cdecl*)();
    using NvAPI_Unload_t = std::int32_t(__cdecl*)();

//    constexpr std::size_t NVAPI_MAX_PHYSICAL_GPUS = 64;
    using NvAPI_EnumPhysicalGPUs_t = std::int32_t(__cdecl*)(void* nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS], std::uint32_t* pGpuCount);
    using NvAPI_GPU_GetFullName_t = std::int32_t(__cdecl*)(void* nvGPUHandle, char* const pGpuName);

    constexpr std::uint32_t offset_NvAPI_Initialize = 0x0150E828UL;
    constexpr std::uint32_t offset_NvAPI_Unload = 0xD22BDD7EUL;
    constexpr std::uint32_t offset_NvAPI_EnumPhysicalGPUs = 0xE5AC921FUL;
    constexpr std::uint32_t offset_NvAPI_GPU_GetFullName = 0xCEEE8E9FUL;

    /*   auto hNvapi = LoadLibrary("nvapi64.dll");
        void* address = GetProcAddress(hNvapi, "nvapi_QueryInterface");
        auto const NvAPI_QueryInterface = reinterpret_cast<NvAPI_QueryInterface_t>(address);
        auto const NvAPI_InitializeRaw = reinterpret_cast<NvAPI_Initialize_t>(NvAPI_QueryInterface(offset_NvAPI_Initialize));*/


    //    using NvAPI_QueryInterface_t =  void* (__cdecl *)(std::uint32_t offset);
    //    auto const& nvapi_QueryInterface = boost::dll::import_alias<NvAPI_QueryInterface_t>("nvapi64.dll", "nvapi_QueryInterface", boost::dll::load_mode::search_system_folders);
    auto const nvapi_QueryInterface = nvapi.get<NvAPI_QueryInterface_t>("nvapi_QueryInterface");
    //    REQUIRE(nvapi_QueryInterface);
    /*
        auto const NvAPI_Initialize = reinterpret_cast<NvAPI_Initialize_t>(nvapi_QueryInterface(offset_NvAPI_Initialize));
        REQUIRE(NvAPI_Initialize);
        REQUIRE(!NvAPI_Initialize());

        auto const NvAPI_EnumPhysicalGPUs = reinterpret_cast<NvAPI_EnumPhysicalGPUs_t>(nvapi_QueryInterface(offset_NvAPI_EnumPhysicalGPUs));
        REQUIRE(NvAPI_EnumPhysicalGPUs);
        std::uint32_t gpuCount = 0;
        std::array<void*, NVAPI_MAX_PHYSICAL_GPUS> gpus;
        REQUIRE(!NvAPI_EnumPhysicalGPUs(gpus.data(), &gpuCount));
    */
    std::uint32_t gpuCount = 0;
    std::array<void*, NVAPI_MAX_PHYSICAL_GPUS> gpus;
    auto const NvAPI_Initialize = reinterpret_cast<NvAPI_Initialize_t>(nvapi_QueryInterface(offset_NvAPI_Initialize));
    REQUIRE(NvAPI_Initialize);
    REQUIRE(!NvAPI_Initialize());
    auto const NvAPI_EnumPhysicalGPUs = reinterpret_cast<NvAPI_EnumPhysicalGPUs_t>(nvapi_QueryInterface(offset_NvAPI_EnumPhysicalGPUs));
    REQUIRE(NvAPI_EnumPhysicalGPUs);
    REQUIRE(!NvAPI_EnumPhysicalGPUs(gpus.data(), &gpuCount));

    auto const NvAPI_GPU_GetFullName = reinterpret_cast<NvAPI_GPU_GetFullName_t>(nvapi_QueryInterface(offset_NvAPI_GPU_GetFullName));
    REQUIRE(NvAPI_GPU_GetFullName);
    using NvAPI_ShortString = std::array<char, NVAPI_SHORT_STRING_MAX>;
    NvAPI_ShortString gpuName;
    REQUIRE(!NvAPI_GPU_GetFullName(gpus[0], gpuName.data()));

    auto const NvAPI_Unload = reinterpret_cast<NvAPI_Initialize_t>(nvapi_QueryInterface(offset_NvAPI_Unload));
    REQUIRE(NvAPI_Unload);
    REQUIRE(!NvAPI_Unload());
}

} // namespace morpheus::gfx::nvidia
