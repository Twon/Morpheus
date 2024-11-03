#pragma once

#include <morpheus/core/base/platform.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
    // Windows first as other Windows header depend on info defined here
    #include <windows.h> // IWYU pragma: export
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)
#endif // #if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
