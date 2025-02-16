#pragma once

#include <cstdint>
#include <morpheus/core/base/compiler.hpp>
#include <morpheus/core/morpheuscore_export.h>

/*! \defgroup Platform Morpheus Supported Platforms
        The platform group of macros allow for compile time detection of the current platform.
    @{
    \def MORPHEUS_BUILD_PLATFORM
        Macro describing the current build platform of the build.
*/
#if !defined(MORPHEUS_BUILD_PLATFORM)

    /*! \def MORPHEUS_TARGET_PLATFORM_PC_WINDOWS
            This token is used to signify the Microsoft Windows PC platform.
     */
    #define MORPHEUS_TARGET_PLATFORM_PC_WINDOWS 1001

    /*! \def MORPHEUS_TARGET_PLATFORM_APPLE
            This token is used to signify the Apple Macintosh PC platform.
     */
    #define MORPHEUS_TARGET_PLATFORM_APPLE      1002

    /*!    \def MORPHEUS_TARGET_PLATFORM_LINUX
            This token is used to signify the Linux PC platform.
     */
    #define MORPHEUS_TARGET_PLATFORM_LINUX      1003

    #if (defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64))

        #define MORPHEUS_BUILD_PLATFORM MORPHEUS_TARGET_PLATFORM_PC_WINDOWS

    #elif defined(__APPLE_CC__)

        #define MORPHEUS_BUILD_PLATFORM MORPHEUS_TARGET_PLATFORM_APPLE

    #elif defined(__linux)

        #define MORPHEUS_BUILD_PLATFORM MORPHEUS_TARGET_PLATFORM_LINUX

    #else

        #define MORPHEUS_BUILD_PLATFORM
        #error "Platform is not currently supported, MORPHEUS libraries will not compile!"

    #endif
#endif
/// @}

/*! \def MORPHEUS_COMPILER_DEAD_CODE_ELIMINATION
        Macro present when dead code elimination is enabled in the build.
*/
#if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER && __OPTIMIZE__) ||                                                           \
    (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER && !defined __MSVC_RUNTIME_CHECKS && defined NDEBUG) ||              \
    defined(__DOXYGEN__)
    #define MORPHEUS_COMPILER_DEAD_CODE_ELIMINATION
#endif
