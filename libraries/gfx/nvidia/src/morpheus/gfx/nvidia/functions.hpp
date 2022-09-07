#pragma once

#include <sal.h>
#include <nvapi.h>

namespace morpheus::gfx::nvidia::nvapi
{

    using NvAPI_QueryInterface_t = void* (__cdecl*)(unsigned int offset);
    using NvAPI_Initialize_t = NvAPI_Status(__cdecl*)();
    using NvAPI_Unload_t = NvAPI_Status(__cdecl*)();
    using NvAPI_GetErrorMessage_t = NvAPI_Status(__cdecl*)(NvAPI_Status nr, NvAPI_ShortString szDesc);
    using NvAPI_GetInterfaceVersionString_t = NvAPI_Status(__cdecl*)(NvAPI_ShortString szDesc);
    using NvAPI_GetInterfaceVersionStringEx_t = NvAPI_Status(__cdecl*)(NvAPI_ShortString szDesc);
    using NvAPI_GPU_GetEDID_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32, NV_EDID*);
    using NvAPI_OGL_ExpertModeSet_t = NvAPI_Status(__cdecl*)(NvU32, NvU32, NvU32, NVAPI_OGLEXPERT_CALLBACK*);
    using NvAPI_OGL_ExpertModeGet_t = NvAPI_Status(__cdecl*)(NvU32*, NvU32*, NvU32*, NVAPI_OGLEXPERT_CALLBACK*);
    using NvAPI_OGL_ExpertModeDefaultsSet_t = NvAPI_Status(__cdecl*)(NvU32, NvU32, NvU32);
    using NvAPI_OGL_ExpertModeDefaultsGet_t = NvAPI_Status(__cdecl*)(NvU32*, NvU32*, NvU32*);
    using NvAPI_EnumPhysicalGPUs_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle*, NvU32*);
    using NvAPI_EnumTCCPhysicalGPUs_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle*, NvU32*);
    using NvAPI_EnumLogicalGPUs_t = NvAPI_Status(__cdecl*)(NvLogicalGpuHandle*, NvU32*);
    using NvAPI_GetPhysicalGPUsFromDisplay_t = NvAPI_Status(__cdecl*)(NvDisplayHandle, NvPhysicalGpuHandle*, NvU32*);
    using NvAPI_GetPhysicalGPUFromUnAttachedDisplay_t = NvAPI_Status(__cdecl*)(NvUnAttachedDisplayHandle, NvPhysicalGpuHandle*);
    using NvAPI_GetLogicalGPUFromDisplay_t = NvAPI_Status(__cdecl*)(NvDisplayHandle, NvLogicalGpuHandle*);
    using NvAPI_GetLogicalGPUFromPhysicalGPU_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvLogicalGpuHandle*);
    using NvAPI_GetPhysicalGPUsFromLogicalGPU_t = NvAPI_Status(__cdecl*)(NvLogicalGpuHandle, NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GetPhysicalGPUFromGPUID_t = NvAPI_Status(__cdecl*)(NvU32, NvPhysicalGpuHandle*);
    using NvAPI_GetGPUIDfromPhysicalGPU_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetShaderSubPipeCount_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetGpuCoreCount_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetConnectedDisplayIds_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_DISPLAYIDS*, NvU32*, NvU32);
    using NvAPI_GPU_GetAllDisplayIds_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_DISPLAYIDS*, NvU32*);
    using NvAPI_GPU_GetSystemType_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_SYSTEM_TYPE*);
    using NvAPI_GPU_GetActiveOutputs_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_SetEDID_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32, NV_EDID*);
    using NvAPI_GPU_GetOutputType_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32, NV_GPU_OUTPUT_TYPE*);
    using NvAPI_GPU_ValidateOutputCombination_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32);
    using NvAPI_GPU_GetFullName_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvAPI_ShortString);
    using NvAPI_GPU_GetPCIIdentifiers_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*, NvU32*, NvU32*, NvU32*);
    using NvAPI_GPU_GetGPUType_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_TYPE*);
    using NvAPI_GPU_GetBusType_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_BUS_TYPE*);
    using NvAPI_GPU_GetBusId_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetBusSlotId_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetIRQ_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetVbiosRevision_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetVbiosOEMRevision_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32);
    using NvAPI_GPU_GetVbiosVersionString_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvAPI_ShortString);
    using NvAPI_GPU_GetCurrentPCIEDownstreamWidth_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetPhysicalFrameBufferSize_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetVirtualFrameBufferSize_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetBoardInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_BOARD_INFO*);
    using NvAPI_GPU_GetArchInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_ARCH_INFO*);
    using NvAPI_I2CRead_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle hPhysicalGpu, NV_I2C_INFO* pI2cInfo);
    using NvAPI_I2CWrite_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle hPhysicalGpu, NV_I2C_INFO* pI2cInfo);
    using NvAPI_GPU_WorkstationFeatureSetup_t = NvAPI_Status(__cdecl*)(__in NvPhysicalGpuHandle hPhysicalGpu, __in NvU32 featureEnableMask, __in NvU32 featureDisableMask);
    using NvAPI_GPU_WorkstationFeatureQuery_t = NvAPI_Status(__cdecl*)(__in NvPhysicalGpuHandle hPhysicalGpu, __out_opt NvU32* pConfiguredFeatureMask, __out_opt NvU32* pConsistentFeatureMask);
    using NvAPI_GPU_GetHDCPSupportStatus_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_GET_HDCP_SUPPORT_STATUS* pGetHDCPSupportStatus);
    using NvAPI_GPU_GetTachReading_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetECCStatusInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_ECC_STATUS_INFO*);
    using NvAPI_GPU_GetECCErrorInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_ECC_ERROR_INFO*);
    using NvAPI_GPU_ResetECCErrorInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU8, NvU8);
    using NvAPI_GPU_GetECCConfigurationInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_ECC_CONFIGURATION_INFO*);
    using NvAPI_GPU_SetECCConfiguration_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU8, NvU8);
    using NvAPI_GPU_QueryWorkstationFeatureSupport_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_WORKSTATION_FEATURE_TYPE);
    using NvAPI_GPU_SetScanoutIntensity_t = NvAPI_Status(__cdecl*)(NvU32, NV_SCANOUT_INTENSITY_DATA*, int*);
    using NvAPI_GPU_GetScanoutIntensityState_t = NvAPI_Status(__cdecl*)(NvU32, NV_SCANOUT_INTENSITY_STATE_DATA*);
    using NvAPI_GPU_SetScanoutWarping_t = NvAPI_Status(__cdecl*)(NvU32, NV_SCANOUT_WARPING_DATA*, int*, int*);
    using NvAPI_GPU_GetScanoutWarpingState_t = NvAPI_Status(__cdecl*)(NvU32, NV_SCANOUT_WARPING_STATE_DATA*);
    using NvAPI_GPU_SetScanoutCompositionParameter_t = NvAPI_Status(__cdecl*)(NvU32, NV_GPU_SCANOUT_COMPOSITION_PARAMETER,NV_GPU_SCANOUT_COMPOSITION_PARAMETER_VALUE, float*);
    using NvAPI_GPU_GetScanoutCompositionParameter_t = NvAPI_Status(__cdecl*)(NvU32, NV_GPU_SCANOUT_COMPOSITION_PARAMETER, NV_GPU_SCANOUT_COMPOSITION_PARAMETER_VALUE*, float*);
    using NvAPI_GPU_GetScanoutConfiguration_t = NvAPI_Status(__cdecl*)(NvU32, NvSBox*, NvSBox*);
    using NvAPI_GPU_GetScanoutConfigurationEx_t = NvAPI_Status(__cdecl*)(NvU32, NV_SCANOUT_INFORMATION*);
    using NvAPI_GPU_GetAdapterIdFromPhysicalGpu_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, void*);
    using NvAPI_GPU_GetVirtualizationInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_VIRTUALIZATION_INFO*);
    using NvAPI_GPU_GetLogicalGpuInfo_t = NvAPI_Status(__cdecl*)(NvLogicalGpuHandle, NV_LOGICAL_GPU_DATA*);
    using NvAPI_GPU_GetLicensableFeatures_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_LICENSABLE_FEATURES*);
    using NvAPI_GPU_GetVRReadyData_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_VR_READY*);
    using NvAPI_GPU_GetPerfDecreaseInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32*);
    using NvAPI_GPU_GetPstates20_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_PERF_PSTATES20_INFO*);
    using NvAPI_GPU_GetCurrentPstate_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_PERF_PSTATE_ID*);
    using NvAPI_GPU_GetDynamicPstatesInfoEx_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_DYNAMIC_PSTATES_INFO_EX*);
    using NvAPI_GPU_GetThermalSettings_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NvU32, NV_GPU_THERMAL_SETTINGS*);
    using NvAPI_GPU_GetAllClockFrequencies_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLOCK_FREQUENCIES*);
    using NvAPI_GPU_QueryIlluminationSupport_t = NvAPI_Status(__cdecl*)(NV_GPU_QUERY_ILLUMINATION_SUPPORT_PARM*);
    using NvAPI_GPU_GetIllumination_t = NvAPI_Status(__cdecl*)(NV_GPU_GET_ILLUMINATION_PARM*);
    using NvAPI_GPU_SetIllumination_t = NvAPI_Status(__cdecl*)(NV_GPU_SET_ILLUMINATION_PARM*);
    using NvAPI_GPU_ClientIllumDevicesGetInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_DEVICE_INFO_PARAMS*);
    using NvAPI_GPU_ClientIllumDevicesGetControl_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_DEVICE_CONTROL_PARAMS*);
    using NvAPI_GPU_ClientIllumDevicesSetControl_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_DEVICE_CONTROL_PARAMS*);
    using NvAPI_GPU_ClientIllumZonesGetInfo_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_ZONE_INFO_PARAMS*);
    using NvAPI_GPU_ClientIllumZonesGetControl_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_ZONE_CONTROL_PARAMS*);
    using NvAPI_GPU_ClientIllumZonesSetControl_t = NvAPI_Status(__cdecl*)(NvPhysicalGpuHandle, NV_GPU_CLIENT_ILLUM_ZONE_CONTROL_PARAMS*);

/*
    
    NVAPI_INTERFACE NvAPI_Event_RegisterCallback(PNV_EVENT_REGISTER_CALLBACK eventCallback,
        NvEventHandle* phClient);
    NVAPI_INTERFACE NvAPI_Event_UnregisterCallback(NvEventHandle hClient);
    NVAPI_INTERFACE NvAPI_EnumNvidiaDisplayHandle(NvU32 thisEnum, NvDisplayHandle* pNvDispHandle);
    NVAPI_INTERFACE NvAPI_EnumNvidiaUnAttachedDisplayHandle(NvU32 thisEnum, NvUnAttachedDisplayHandle* pNvUnAttachedDispHandle);
    NVAPI_INTERFACE NvAPI_CreateDisplayFromUnAttachedDisplay(NvUnAttachedDisplayHandle hNvUnAttachedDisp, NvDisplayHandle* pNvDisplay);
    NVAPI_INTERFACE NvAPI_GetAssociatedNvidiaDisplayHandle(const char* szDisplayName, NvDisplayHandle* pNvDispHandle);
    NVAPI_INTERFACE NvAPI_DISP_GetAssociatedUnAttachedNvidiaDisplayHandle(const char* szDisplayName, NvUnAttachedDisplayHandle* pNvUnAttachedDispHandle);
    NVAPI_INTERFACE NvAPI_GetAssociatedNvidiaDisplayName(NvDisplayHandle NvDispHandle, NvAPI_ShortString szDisplayName);
    NVAPI_INTERFACE NvAPI_GetUnAttachedAssociatedDisplayName(NvUnAttachedDisplayHandle hNvUnAttachedDisp, NvAPI_ShortString szDisplayName);
    NVAPI_INTERFACE NvAPI_EnableHWCursor(NvDisplayHandle hNvDisplay);
    NVAPI_INTERFACE NvAPI_DisableHWCursor(NvDisplayHandle hNvDisplay);
    NVAPI_INTERFACE NvAPI_GetVBlankCounter(NvDisplayHandle hNvDisplay, NvU32* pCounter);
    NVAPI_INTERFACE NvAPI_SetRefreshRateOverride(NvDisplayHandle hNvDisplay, NvU32 outputsMask, float refreshRate, NvU32 bSetDeferred);
    NVAPI_INTERFACE NvAPI_GetAssociatedDisplayOutputId(NvDisplayHandle hNvDisplay, NvU32* pOutputId);
    NVAPI_INTERFACE NvAPI_GetDisplayPortInfo(__in_opt NvDisplayHandle hNvDisplay, __in NvU32 outputId, __inout NV_DISPLAY_PORT_INFO* pInfo);
    NVAPI_INTERFACE NvAPI_SetDisplayPort(NvDisplayHandle hNvDisplay, NvU32 outputId, NV_DISPLAY_PORT_CONFIG* pCfg);
    NVAPI_INTERFACE NvAPI_GetHDMISupportInfo(__in_opt NvDisplayHandle hNvDisplay, __in NvU32 outputId, __inout NV_HDMI_SUPPORT_INFO* pInfo);
    NVAPI_INTERFACE NvAPI_Disp_InfoFrameControl(__in NvU32 displayId, __inout NV_INFOFRAME_DATA* pInfoframeData);
    NVAPI_INTERFACE NvAPI_Disp_ColorControl(NvU32 displayId, NV_COLOR_DATA* pColorData);
    NVAPI_INTERFACE NvAPI_Disp_GetHdrCapabilities(__in NvU32 displayId, __inout NV_HDR_CAPABILITIES* pHdrCapabilities);
    NVAPI_INTERFACE NvAPI_Disp_HdrColorControl(__in NvU32 displayId, __inout NV_HDR_COLOR_DATA* pHdrColorData);
    NVAPI_INTERFACE NvAPI_DISP_GetTiming(__in NvU32 displayId, __in NV_TIMING_INPUT* timingInput, __out NV_TIMING* pTiming);
    NVAPI_INTERFACE NvAPI_DISP_GetMonitorCapabilities(__in NvU32 displayId, __inout NV_MONITOR_CAPABILITIES* pMonitorCapabilities);
    NVAPI_INTERFACE NvAPI_DISP_GetMonitorColorCapabilities(__in NvU32 displayId, __inout_ecount_part_opt(*pColorCapsCount, *pColorCapsCount) NV_MONITOR_COLOR_CAPS* pMonitorColorCapabilities, __inout NvU32* pColorCapsCount);
    NVAPI_INTERFACE NvAPI_DISP_EnumCustomDisplay(__in NvU32 displayId, __in NvU32 index, __inout NV_CUSTOM_DISPLAY* pCustDisp);
    NVAPI_INTERFACE NvAPI_DISP_TryCustomDisplay(__in_ecount(count) NvU32* pDisplayIds, __in NvU32 count, __in_ecount(count) NV_CUSTOM_DISPLAY* pCustDisp);
    NVAPI_INTERFACE NvAPI_DISP_DeleteCustomDisplay(__in_ecount(count) NvU32* pDisplayIds, __in NvU32 count, __in NV_CUSTOM_DISPLAY* pCustDisp);
    NVAPI_INTERFACE NvAPI_DISP_SaveCustomDisplay(__in_ecount(count) NvU32* pDisplayIds, __in NvU32 count, __in NvU32 isThisOutputIdOnly, __in NvU32 isThisMonitorIdOnly);
    NVAPI_INTERFACE NvAPI_DISP_RevertCustomDisplayTrial(__in_ecount(count) NvU32* pDisplayIds, __in NvU32 count);
    NVAPI_INTERFACE NvAPI_GetSupportedViews(NvDisplayHandle hNvDisplay, NV_TARGET_VIEW_MODE* pTargetViews, NvU32* pViewCount);
    NVAPI_INTERFACE NvAPI_DISP_GetDisplayIdByDisplayName(const char* displayName, NvU32* displayId);
    NVAPI_INTERFACE NvAPI_DISP_GetDisplayConfig(__inout NvU32* pathInfoCount, __out_ecount_full_opt(*pathInfoCount) NV_DISPLAYCONFIG_PATH_INFO* pathInfo);
    NVAPI_INTERFACE NvAPI_DISP_SetDisplayConfig(__in NvU32 pathInfoCount, __in_ecount(pathInfoCount) NV_DISPLAYCONFIG_PATH_INFO* pathInfo, __in NvU32 flags);
    NVAPI_INTERFACE NvAPI_DISP_GetAdaptiveSyncData(__in NvU32 displayId, __inout NV_GET_ADAPTIVE_SYNC_DATA* pAdaptiveSyncData);
    NVAPI_INTERFACE NvAPI_DISP_SetAdaptiveSyncData(__in NvU32 displayId, __in NV_SET_ADAPTIVE_SYNC_DATA* pAdaptiveSyncData);
    NVAPI_INTERFACE NvAPI_DISP_GetVirtualRefreshRateData(__in NvU32 displayId, __inout NV_GET_VIRTUAL_REFRESH_RATE_DATA* pVirtualRefreshRateData);
    NVAPI_INTERFACE NvAPI_DISP_SetVirtualRefreshRateData(__in NvU32 displayId, __in NV_SET_VIRTUAL_REFRESH_RATE_DATA* pVirtualRefreshRateData);
    NVAPI_INTERFACE NvAPI_DISP_SetPreferredStereoDisplay(__in NV_SET_PREFERRED_STEREO_DISPLAY* pPreferredStereoDisplay);
    NVAPI_INTERFACE NvAPI_DISP_GetPreferredStereoDisplay(__inout NV_GET_PREFERRED_STEREO_DISPLAY* pPreferredStereoDisplay);
    NVAPI_INTERFACE NvAPI_DISP_GetNvManagedDedicatedDisplays(__inout NvU32* pDedicatedDisplayCount, __inout NV_MANAGED_DEDICATED_DISPLAY_INFO* pDedicatedDisplays);
    NVAPI_INTERFACE NvAPI_DISP_AcquireDedicatedDisplay(__in NvU32 displayId, __inout NvU64* pDisplaySourceHandle);
    NVAPI_INTERFACE NvAPI_DISP_ReleaseDedicatedDisplay(__in NvU32 displayId);
    NVAPI_INTERFACE NvAPI_Mosaic_GetSupportedTopoInfo(NV_MOSAIC_SUPPORTED_TOPO_INFO* pSupportedTopoInfo, NV_MOSAIC_TOPO_TYPE type);
    NVAPI_INTERFACE NvAPI_Mosaic_GetTopoGroup(NV_MOSAIC_TOPO_BRIEF* pTopoBrief, NV_MOSAIC_TOPO_GROUP* pTopoGroup);
    NVAPI_INTERFACE NvAPI_Mosaic_GetOverlapLimits(NV_MOSAIC_TOPO_BRIEF* pTopoBrief, NV_MOSAIC_DISPLAY_SETTING* pDisplaySetting, NvS32* pMinOverlapX, NvS32* pMaxOverlapX, NvS32* pMinOverlapY, NvS32* pMaxOverlapY);
    NVAPI_INTERFACE NvAPI_Mosaic_SetCurrentTopo(NV_MOSAIC_TOPO_BRIEF* pTopoBrief, NV_MOSAIC_DISPLAY_SETTING* pDisplaySetting, NvS32 overlapX, NvS32 overlapY, NvU32 enable);
    NVAPI_INTERFACE NvAPI_Mosaic_GetCurrentTopo(NV_MOSAIC_TOPO_BRIEF* pTopoBrief, NV_MOSAIC_DISPLAY_SETTING* pDisplaySetting, NvS32* pOverlapX, NvS32* pOverlapY);
    NVAPI_INTERFACE NvAPI_Mosaic_EnableCurrentTopo(NvU32 enable);
    NVAPI_INTERFACE NvAPI_Mosaic_SetDisplayGrids(__in_ecount(gridCount) NV_MOSAIC_GRID_TOPO* pGridTopologies, __in NvU32 gridCount, __in NvU32 setTopoFlags);
    NVAPI_INTERFACE NvAPI_Mosaic_ValidateDisplayGrids(__in NvU32 setTopoFlags,
        __in_ecount(gridCount) NV_MOSAIC_GRID_TOPO* pGridTopologies,
        __inout_ecount_full(gridCount) NV_MOSAIC_DISPLAY_TOPO_STATUS* pTopoStatus,
        __in NvU32 gridCount);
    NVAPI_INTERFACE NvAPI_Mosaic_EnumDisplayModes(__in NV_MOSAIC_GRID_TOPO* pGridTopology,
        __inout_ecount_part_opt(*pDisplayCount, *pDisplayCount) NV_MOSAIC_DISPLAY_SETTING* pDisplaySettings,
        __inout NvU32* pDisplayCount);
    NVAPI_INTERFACE NvAPI_Mosaic_EnumDisplayGrids(__inout_ecount_part_opt(*pGridCount, *pGridCount) NV_MOSAIC_GRID_TOPO* pGridTopologies,
        __inout NvU32* pGridCount);
    NVAPI_INTERFACE NvAPI_GetSupportedMosaicTopologies(NV_MOSAIC_SUPPORTED_TOPOLOGIES* pMosaicTopos);
    NVAPI_INTERFACE NvAPI_GetCurrentMosaicTopology(NV_MOSAIC_TOPOLOGY* pMosaicTopo, NvU32* pEnabled);
    NVAPI_INTERFACE NvAPI_SetCurrentMosaicTopology(NV_MOSAIC_TOPOLOGY* pMosaicTopo);
    NVAPI_INTERFACE NvAPI_EnableCurrentMosaicTopology(NvU32 enable);
    NVAPI_INTERFACE NvAPI_GSync_EnumSyncDevices(__out NvGSyncDeviceHandle nvGSyncHandles[NVAPI_MAX_GSYNC_DEVICES], __out NvU32* gsyncCount);
    NVAPI_INTERFACE NvAPI_GSync_QueryCapabilities(__in NvGSyncDeviceHandle hNvGSyncDevice, __inout NV_GSYNC_CAPABILITIES* pNvGSyncCapabilities);
    NVAPI_INTERFACE NvAPI_GSync_GetTopology(__in NvGSyncDeviceHandle hNvGSyncDevice, __inout_opt NvU32* gsyncGpuCount, __inout_ecount_part_opt(*gsyncGpuCount, *gsyncGpuCount) NV_GSYNC_GPU* gsyncGPUs,
        __inout_opt NvU32* gsyncDisplayCount, __inout_ecount_part_opt(*gsyncDisplayCount, *gsyncDisplayCount) NV_GSYNC_DISPLAY* gsyncDisplays);
    NVAPI_INTERFACE NvAPI_GSync_SetSyncStateSettings(__in NvU32 gsyncDisplayCount, __in_ecount(gsyncDisplayCount) NV_GSYNC_DISPLAY* pGsyncDisplays, __in NvU32 flags);
    NVAPI_INTERFACE NvAPI_GSync_GetControlParameters(__in NvGSyncDeviceHandle hNvGSyncDevice, __inout NV_GSYNC_CONTROL_PARAMS* pGsyncControls);
    NVAPI_INTERFACE NvAPI_GSync_SetControlParameters(__in NvGSyncDeviceHandle hNvGSyncDevice, __inout NV_GSYNC_CONTROL_PARAMS* pGsyncControls);
    NVAPI_INTERFACE NvAPI_GSync_AdjustSyncDelay(__in NvGSyncDeviceHandle hNvGSyncDevice, __in NVAPI_GSYNC_DELAY_TYPE delayType, __inout NV_GSYNC_DELAY* pGsyncDelay, __out_opt NvU32* syncSteps);
    NVAPI_INTERFACE NvAPI_GSync_GetSyncStatus(__in NvGSyncDeviceHandle hNvGSyncDevice, __in NvPhysicalGpuHandle hPhysicalGpu, __inout NV_GSYNC_STATUS* status);
    NVAPI_INTERFACE NvAPI_GSync_GetStatusParameters(NvGSyncDeviceHandle hNvGSyncDevice, NV_GSYNC_STATUS_PARAMS* pStatusParams);
#if defined(_D3D9_H_)
    NVAPI_INTERFACE NvAPI_D3D9_RegisterResource(IDirect3DResource9* pResource);
    NVAPI_INTERFACE NvAPI_D3D9_UnregisterResource(IDirect3DResource9* pResource);
    NVAPI_INTERFACE NvAPI_D3D9_AliasSurfaceAsTexture(IDirect3DDevice9* pDev,
        IDirect3DSurface9* pSurface,
        IDirect3DTexture9** ppTexture,
        DWORD dwFlag);
    NVAPI_INTERFACE NvAPI_D3D9_StretchRectEx(IDirect3DDevice9* pDevice,
        IDirect3DResource9* pSourceResource,
        CONST RECT* pSourceRect,
        IDirect3DResource9* pDestResource,
        CONST RECT* pDestRect,
        D3DTEXTUREFILTERTYPE Filter);
    NVAPI_INTERFACE NvAPI_D3D9_ClearRT(IDirect3DDevice9* pDevice,
        NvU32 dwNumRects,
        CONST RECT* pRects,
        float r, float g, float b, float a);
    NVAPI_INTERFACE NvAPI_D3D9_GetSurfaceHandle(IDirect3DSurface9* pSurface,
        NVDX_ObjectHandle* pHandle);
    NVAPI_INTERFACE NvAPI_D3D9_VideoSetStereoInfo(IDirect3DDevice9* pDev,
        NV_DX_VIDEO_STEREO_INFO* pStereoInfo);
#endif //defined(_D3D9_H_)


#if defined(__cplusplus) && defined(__d3d10_h__)
    NVAPI_INTERFACE NvAPI_D3D10_SetDepthBoundsTest(ID3D10Device* pDev,
        NvU32 bEnable,
        float fMinDepth,
        float fMaxDepth);
#endif //defined(__cplusplus) && defined(__d3d10_h__)


#if defined (__cplusplus) && (defined(__d3d11_h__) || defined(__d3d11_1_h__))
    NVAPI_INTERFACE NvAPI_D3D11_IsNvShaderExtnOpCodeSupported(__in  IUnknown* pDev,
        __in  NvU32 opCode,
        __out bool* pSupported);
    NVAPI_INTERFACE NvAPI_D3D11_SetNvShaderExtnSlot(__in IUnknown* pDev,
        __in NvU32 uavSlot);
#endif //defined (__cplusplus) && (defined(__d3d11_h__) || defined(__d3d11_1_h__))


#if defined (__cplusplus) && defined (__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_SetNvShaderExtnSlotSpace(__in IUnknown* pDev,
        __in NvU32 uavSlot,
        __in NvU32 uavSpace);
#endif //defined (__cplusplus) && defined (__d3d12_h__)


#if defined (__cplusplus) && (defined(__d3d11_h__) || defined(__d3d11_1_h__))
    NVAPI_INTERFACE NvAPI_D3D11_SetNvShaderExtnSlotLocalThread(__in IUnknown* pDev,
        __in NvU32 uavSlot);
    NVAPI_INTERFACE NvAPI_D3D11_BeginUAVOverlapEx(__in  IUnknown* pDeviceOrContext, __in NvU32 insertWFIFlags);
    NVAPI_INTERFACE NvAPI_D3D11_BeginUAVOverlap(__in  IUnknown* pDeviceOrContext);
    NVAPI_INTERFACE NvAPI_D3D11_EndUAVOverlap(__in  IUnknown* pDeviceOrContext);
#endif //defined (__cplusplus) && (defined(__d3d11_h__) || defined(__d3d11_1_h__))


#if defined(__cplusplus) && defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D11_GetResourceHandle(ID3D11Device* pDev,
        ID3D11Resource* pResource,
        NVDX_ObjectHandle* phObject);
#endif //defined(__cplusplus) && defined(__d3d11_h__)


#if defined(_D3D9_H_) || defined(__d3d10_h__) || defined(__d3d10_1_h__) || defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D_SetFPSIndicatorState(IUnknown* pDev, NvU8 doEnable);
#endif //if defined(_D3D9_H_) || defined(__d3d10_h__) || defined(__d3d10_1_h__) || defined(__d3d11_h__)

#if defined(_D3D9_H_)
    NVAPI_INTERFACE NvAPI_D3D9_Present(IDirect3DDevice9* pDevice,
        IDirect3DSwapChain9* pSwapChain,
        const RECT* pSourceRect,
        const RECT* pDestRect,
        HWND hDestWindowOverride,
        const RGNDATA* pDirtyRegion);
    NVAPI_INTERFACE NvAPI_D3D9_QueryFrameCount(IDirect3DDevice9* pDevice,
        NvU32* pFrameCount);
    NVAPI_INTERFACE NvAPI_D3D9_ResetFrameCount(IDirect3DDevice9* pDevice);
    NVAPI_INTERFACE NvAPI_D3D9_QueryMaxSwapGroup(IDirect3DDevice9* pDevice,
        NvU32* pMaxGroups,
        NvU32* pMaxBarriers);
    NVAPI_INTERFACE NvAPI_D3D9_QuerySwapGroup(IDirect3DDevice9* pDevice,
        IDirect3DSwapChain9* pSwapChain,
        NvU32* pSwapGroup,
        NvU32* pSwapBarrier);
    NVAPI_INTERFACE NvAPI_D3D9_JoinSwapGroup(IDirect3DDevice9* pDevice,
        IDirect3DSwapChain9* pSwapChain,
        NvU32 group,
        BOOL blocking);
    NVAPI_INTERFACE NvAPI_D3D9_BindSwapBarrier(IDirect3DDevice9* pDevice,
        NvU32 group,
        NvU32 barrier);
#endif //if defined(_D3D9_H_)

#if defined(__d3d10_h__) || defined(__d3d10_1_h__) || defined(__d3d11_h__) || defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D1x_Present(IUnknown* pDevice,
        IDXGISwapChain* pSwapChain,
        UINT SyncInterval,
        UINT Flags);
    NVAPI_INTERFACE NvAPI_D3D1x_QueryFrameCount(IUnknown* pDevice,
        NvU32* pFrameCount);
    NVAPI_INTERFACE NvAPI_D3D1x_ResetFrameCount(IUnknown* pDevice);
    NVAPI_INTERFACE NvAPI_D3D1x_QueryMaxSwapGroup(IUnknown* pDevice,
        NvU32* pMaxGroups,
        NvU32* pMaxBarriers);
    NVAPI_INTERFACE NvAPI_D3D1x_QuerySwapGroup(IUnknown* pDevice,
        IDXGISwapChain* pSwapChain,
        NvU32* pSwapGroup,
        NvU32* pSwapBarrier);
    NVAPI_INTERFACE NvAPI_D3D1x_JoinSwapGroup(IUnknown* pDevice,
        IDXGISwapChain* pSwapChain,
        NvU32 group,
        BOOL blocking);
    NVAPI_INTERFACE NvAPI_D3D1x_BindSwapBarrier(IUnknown* pDevice,
        NvU32 group,
        NvU32 barrier);
#endif // defined(__d3d10_h__) || defined(__d3d10_1_h__) || defined(__d3d11_h__) || defined(__d3d12_h__)

#if defined(__cplusplus) && defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_QueryPresentBarrierSupport(__in ID3D12Device* pDevice, __out bool* pSupported);
    NVAPI_INTERFACE NvAPI_D3D12_CreatePresentBarrierClient(__in ID3D12Device* pDevice,
        __in IDXGISwapChain* pSwapChain,
        __out NvPresentBarrierClientHandle* pPresentBarrierClient);
    NVAPI_INTERFACE NvAPI_D3D12_RegisterPresentBarrierResources(__in NvPresentBarrierClientHandle presentBarrierClient,
        __in ID3D12Fence* pFence,
        __in ID3D12Resource** ppResources,
        __in NvU32                        numResources);
#endif // defined(__cplusplus) && defined(__d3d12_h__)

    NVAPI_INTERFACE NvAPI_DestroyPresentBarrierClient(__in NvPresentBarrierClientHandle presentBarrierClient);
    NVAPI_INTERFACE NvAPI_JoinPresentBarrier(__in NvPresentBarrierClientHandle presentBarrierClient, __in NV_JOIN_PRESENT_BARRIER_PARAMS* pParams);
    NVAPI_INTERFACE NvAPI_LeavePresentBarrier(__in NvPresentBarrierClientHandle presentBarrierClient);
    NVAPI_INTERFACE NvAPI_QueryPresentBarrierFrameStatistics(__in NvPresentBarrierClientHandle presentBarrierClient,
        __out NV_PRESENT_BARRIER_FRAME_STATISTICS* pFrameStats);

#if defined(__cplusplus) && defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_CreateDDisplayPresentBarrierClient(__in ID3D12Device* pDevice, __in NvU32 sourceId, __out NvPresentBarrierClientHandle* pPresentBarrierClient);
#endif // defined(__cplusplus) && defined(__d3d12_h__)


#if defined(__cplusplus) && defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D11_CreateRasterizerState(__in ID3D11Device* pDevice,
        __in const NvAPI_D3D11_RASTERIZER_DESC_EX* pRasterizerDesc,
        __out ID3D11RasterizerState** ppRasterizerState)
#endif //defined(__cplusplus) && defined(__d3d11_h__)


#if defined (__cplusplus) && (defined(_D3D9_H_) || defined(__d3d11_h__) || defined(__d3d11_1_h__) || defined(__d3d12_h__))
        NVAPI_INTERFACE NvAPI_D3D_ConfigureAnsel(__in IUnknown* pDevice,
            __in NVAPI_ANSEL_CONFIGURATION_STRUCT* pNLSConfig);
#endif //defined (__cplusplus) && (defined(_D3D9_H_) || defined(__d3d11_h__) || defined(__d3d11_1_h__) || defined(__d3d12_h__))


#if defined(__cplusplus) && defined(__d3d11_2_h__)
    NVAPI_INTERFACE NvAPI_D3D11_CreateTiledTexture2DArray(__in       ID3D11Device* pDevice,
        __in const D3D11_TEXTURE2D_DESC* pDesc,
        __in const D3D11_SUBRESOURCE_DATA* pInitialData,
        __out      ID3D11Texture2D** ppTexture2D);
#endif //defined(__cplusplus) && defined(__d3d11_2_h__)


#if defined(__cplusplus) && defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D11_CheckFeatureSupport(__in  ID3D11Device* pDevice,
        __in  NV_D3D11_FEATURE    Feature,
        __out void* pFeatureSupportData,
        __in  UINT                FeatureSupportDataSize);
    NVAPI_INTERFACE NvAPI_D3D11_CreateImplicitMSAATexture2D(__in  ID3D11Device* pDevice,
        __in  const D3D11_TEXTURE2D_DESC* pDesc,
        __out ID3D11Texture2D** ppTexture2D);
#endif //defined(__cplusplus) && defined(__d3d11_h__)


#if defined(__cplusplus) && defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_CreateCommittedImplicitMSAATexture2D(
        __in  ID3D12Device* pDevice,
        __in  const D3D12_HEAP_PROPERTIES* pHeapProperties,
        D3D12_HEAP_FLAGS HeapFlags,
        __in  const D3D12_RESOURCE_DESC* pDesc,
        D3D12_RESOURCE_STATES InitialResourceState,
        __in_opt  const D3D12_CLEAR_VALUE* pOptimizedClearValue,
        REFIID riidResource,
        __out void** ppvResource);
#endif //defined(__cplusplus) && defined(__d3d12_h__)

#if defined (__cplusplus) && defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D11_ResolveSubresourceRegion(
        __in  ID3D11Device* pDevice,
        __in  ID3D11Texture2D* pDstResource,
        __in  UINT              DstSubresource,
        __in  UINT              DstX,
        __in  UINT              DstY,
        __in  ID3D11Texture2D* pSrcResource,
        __in  UINT              SrcSubresource,
        __in_opt const RECT* pSrcRect,
        __in  DXGI_FORMAT       Format,
        __in  NV_RESOLVE_MODE   ResolveMode);
#endif //defined(__cplusplus) && defined(__d3d11_h__)

#if defined (__cplusplus) && defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_ResolveSubresourceRegion(
        __in     ID3D12GraphicsCommandList1* pCommandList,
        __in     ID3D12Resource* pDstResource,
        __in     UINT                       DstSubresource,
        __in     UINT                       DstX,
        __in     UINT                       DstY,
        __in     ID3D12Resource* pSrcResource,
        __in     UINT                       SrcSubresource,
        __in_opt RECT* pSrcRect,
        __in     DXGI_FORMAT                Format,
        __in     NV_RESOLVE_MODE            ResolveMode);
#endif //defined(__cplusplus) && defined(__d3d12_h__)


#if defined (__cplusplus) && defined(__d3d11_2_h__)
    NVAPI_INTERFACE NvAPI_D3D11_TiledTexture2DArrayGetDesc(__in  ID3D11Texture2D* pTiledTexture2DArray,
        __out D3D11_TEXTURE2D_DESC* pDesc);
    NVAPI_INTERFACE NvAPI_D3D11_UpdateTileMappings(
        __in       ID3D11DeviceContext2* pDeviceContext,
        __in       ID3D11Resource* pTiledResource,
        __in       UINT                             NumTiledResourceRegions,
        __in const D3D11_TILED_RESOURCE_COORDINATE* pTiledResourceRegionStartCoordinates,
        __in const D3D11_TILE_REGION_SIZE* pTiledResourceRegionSizes,
        __in       ID3D11Buffer* pTilePool,
        __in       UINT                             NumRanges,
        __in const UINT* pRangeFlags,
        __in const UINT* pTilePoolStartOffsets,
        __in const UINT* pRangeTileCounts,
        __in       UINT                             Flags);
    NVAPI_INTERFACE NvAPI_D3D11_CopyTileMappings(
        __in       ID3D11DeviceContext* pDeviceContext,
        __in       ID3D11Resource* pDestTiledResource,
        __in const D3D11_TILED_RESOURCE_COORDINATE* pDestRegionStartCoordinate,
        __in       ID3D11Resource* pSourceTiledResource,
        __in const D3D11_TILED_RESOURCE_COORDINATE* pSourceRegionStartCoordinate,
        __in const D3D11_TILE_REGION_SIZE* pTileRegionSize,
        __in       UINT                             Flags);
    NVAPI_INTERFACE NvAPI_D3D11_TiledResourceBarrier(
        __in       ID3D11DeviceContext* pDeviceContext,
        __in       ID3D11Resource* pTiledResourceAccessBeforeBarrier,
        __in       ID3D11Resource* pTiledResourceAccessAfterBarrier);
#endif //defined(__cplusplus) && defined(__d3d11_2_h__)


#if defined (__cplusplus) && (defined(__d3d11_h__) || defined(__d3d11_1_h__))
    NVAPI_INTERFACE NvAPI_D3D11_AliasMSAATexture2DAsNonMSAA(__in ID3D11Device* pDevice,
        __in ID3D11Texture2D* pInputTex,
        __out ID3D11Texture2D** ppOutTex);

#endif //defined(__cplusplus) && defined(__d3d11_h__)


#if defined (__cplusplus) && defined(__d3d11_h__) && (!defined(CINTERFACE))
    NVAPI_INTERFACE NvAPI_D3D11_CreateGeometryShaderEx_2(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_GEOMETRY_SHADER_EX* pCreateGeometryShaderExArgs,
        __out ID3D11GeometryShader** ppGeometryShader);
#endif //defined(__cplusplus) && defined(__d3d11_h__) && (!defined(CINTERFACE))


#if defined (__cplusplus) && defined(__d3d11_h__) && (!defined(CINTERFACE) ) 
    NVAPI_INTERFACE NvAPI_D3D11_CreateVertexShaderEx(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_VERTEX_SHADER_EX* pCreateVertexShaderExArgs,
        __out ID3D11VertexShader** ppVertexShader);
    NVAPI_INTERFACE NvAPI_D3D11_CreateHullShaderEx(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_HULL_SHADER_EX* pCreateHullShaderExArgs,
        __out ID3D11HullShader** ppHullShader);
    NVAPI_INTERFACE NvAPI_D3D11_CreateDomainShaderEx(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_DOMAIN_SHADER_EX* pCreateDomainShaderExArgs,
        __out ID3D11DomainShader** ppDomainShader);
    NVAPI_INTERFACE NvAPI_D3D11_CreatePixelShaderEx_2(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_PIXEL_SHADER_EX* pCreatePixelShaderExArgs,
        __out ID3D11PixelShader** ppPixelShader);
    NVAPI_INTERFACE NvAPI_D3D11_CreateFastGeometryShaderExplicit(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __in const NvAPI_D3D11_CREATE_FASTGS_EXPLICIT_DESC* pCreateFastGSArgs,
        __out ID3D11GeometryShader** ppGeometryShader);
    NVAPI_INTERFACE NvAPI_D3D11_CreateFastGeometryShader(__in ID3D11Device* pDevice, __in const void* pShaderBytecode,
        __in SIZE_T BytecodeLength, __in_opt ID3D11ClassLinkage* pClassLinkage,
        __out ID3D11GeometryShader** ppGeometryShader);
#endif //defined(__cplusplus) && defined(__d3d11_h__) && (!defined(CINTERFACE))


#if defined (__cplusplus) && defined(__d3d11_h__)
    NVAPI_INTERFACE NvAPI_D3D11_DecompressView(__in ID3D11Device* pDevice, __in ID3D11DeviceContext* pDeviceContext, __in ID3D11View* pView);
#endif //defined(__cplusplus) && defined(__d3d11_h__)


#if defined (__cplusplus) && defined(__d3d12_h__)
    NVAPI_INTERFACE NvAPI_D3D12_CreateGraphicsPipelineState(__in ID3D12Device* pDevice,
        __in const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pPSODesc,
        NvU32 numExtensions,
        __in const NVAPI_D3D12_PSO_EXTENSION_DESC** ppExtensions,
        __out ID3D12PipelineState** ppPSO);
    NVAPI_INTERFACE NvAPI_D3D12_CreateComputePipelineState(__in ID3D12Device* pDevice,
        __in const D3D12_COMPUTE_PIPELINE_STATE_DESC* pPSODesc,
        NvU32 numExtensions,
        __in const NVAPI_D3D12_PSO_EXTENSION_DESC** ppExtensions,
        __out ID3D12PipelineState** ppPSO);
    NVAPI_INTERFACE NvAPI_D3D12_SetDepthBoundsTestValues(__in ID3D12GraphicsCommandList* pCommandList,
        __in const float minDepth,
        __in const float maxDepth);
    NVAPI_INTERFACE NvAPI_D3D12_CreateReservedResource(__in       ID3D12Device* pDevice,
        __in const D3D12_RESOURCE_DESC* pDesc,
        __in       D3D12_RESOURCE_STATES   InitialState,
        __in const D3D12_CLEAR_VALUE* pOptimizedClearValue,
        __in       REFIID                  riid,
        __out      void** ppvResource,
        __in       bool                    bTexture2DArrayMipPack,
        __in       ID3D12Heap* pHeap);
    NVAPI_INTERFACE NvAPI_D3D12_CreateHeap(__in       ID3D12Device* pDevice,
        __in const D3D12_HEAP_DESC* pDesc,
        __in       REFIID            riid,
        __out      void** ppvHeap);
    NVAPI_INTERFACE NvAPI_D3D12_CreateHeap2(__in       ID3D12Device* pDevice,
        __in const D3D12_HEAP_DESC* pDesc,
        __in const NV_HEAP_PARAMS* pNVHeapParams,
        __in       REFIID               riid,
        __out      void** ppvHeap);
    NVAPI_INTERFACE NvAPI_D3D12_QueryCpuVisibleVidmem(__in       ID3D12Device* pDevice,
        __out      NvU64* pTotalBytes,
        __out      NvU64* pFreeBytes);
    NVAPI_INTERFACE NvAPI_D3D12_ReservedResourceGetDesc(__in  ID3D12Resource* pReservedResource,
        __out D3D12_RESOURCE_DESC* pDesc)
        NVAPI_INTERFACE NvAPI_D3D12_UpdateTileMappings(
            __in       ID3D12CommandQueue* pCommandQueue,
            __in       ID3D12Resource* pResource,
            __in       UINT                             NumResourceRegions,
            __in const D3D12_TILED_RESOURCE_COORDINATE* pResourceRegionStartCoordinates,
            __in const D3D12_TILE_REGION_SIZE* pResourceRegionSizes,
            __in       ID3D12Heap* pHeap,
            __in       UINT                             NumRanges,
            __in const D3D12_TILE_RANGE_FLAGS* pRangeFlags,
            __in const UINT* pHeapRangeStartOffsets,
            __in const UINT* pRangeTileCounts,
            __in       D3D12_TILE_MAPPING_FLAGS         Flags);
    NVAPI_INTERFACE NvAPI_D3D12_CopyTileMappings(
        __in       ID3D12CommandQueue* pCommandQueue,
        __in       ID3D12Resource* pDstResource,
        __in const D3D12_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate,
        __in       ID3D12Resource* pSrcResource,
        __in const D3D12_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate,
        __in const D3D12_TILE_REGION_SIZE* pRegionSize,
        __in       D3D12_TILE_MAPPING_FLAGS         Flags);
    NVAPI_INTERFACE NvAPI_D3D12_ResourceAliasingBarrier(
        __in       ID3D12GraphicsCommandList* pCommandList,
        __in       UINT                       NumBarriers,
        __in const D3D12_RESOURCE_BARRIER* pBarriers);
    NVAPI_INTERFACE NvAPI_D3D12_CaptureUAVInfo(__in  ID3D12Device* pDevice,
        __out NVAPI_UAV_INFO* pUAVInfo);S
#endif //defined(__cplusplus) && defined(__d3d12_h__)

#if defined (__cplusplus) && defined(__d3d11_h__)
        NVAPI_INTERFACE NvAPI_D3D11_EnumerateMetaCommands(__in                                  ID3D11Device* pDevice,
            __inout                               NvU32* pNumMetaCommands,
            __out_ecount_opt(*pNumMetaCommands)   NVAPI_META_COMMAND_DESC* pDescs);
#endif //defined(__cplusplus) && defined(__d3d11_h__)
*/
} // namespace morpheus::gfx::nvidia::nvapi