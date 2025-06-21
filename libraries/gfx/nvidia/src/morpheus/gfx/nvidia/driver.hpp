#pragma once

#include <morpheus/gfx/nvidia/functions.hpp>

#include <boost/dll/shared_library.hpp>
#include <string_view>
#include <nvapi.h>

namespace morpheus::gfx::nvidia
{

namespace nvapi
{

/// \class Driver
///     A class that provides access to the NVIDIA NVAPI driver functions.
///     This class loads the NVAPI library and provides access to its functions.
class Driver
{
    boost::dll::shared_library mNvapi;

public:

    Driver();
    ~Driver();

    Driver(Driver const&) = delete;
    Driver& operator=(Driver const&) = delete;

    Driver(Driver&&) = delete;
    Driver& operator=(Driver&&) = delete;


    NvAPI_QueryInterface_t NvAPI_QueryInterface;
    NvAPI_Initialize_t NvAPI_Initialize;
    NvAPI_Unload_t NvAPI_Unload;
    NvAPI_GetErrorMessage_t NvAPI_GetErrorMessage;
    NvAPI_EnumPhysicalGPUs_t NvAPI_EnumPhysicalGPUs;
    NvAPI_GPU_GetFullName_t NvAPI_GPU_GetFullName;
    NvAPI_GPU_GetAdapterIdFromPhysicalGpu_t NvAPI_GPU_GetAdapterIdFromPhysicalGpu;
    NvAPI_GPU_GetAllDisplayIds_t NvAPI_GPU_GetAllDisplayIds;
};

}

} // namespace morpheus::gfx::nvidia
