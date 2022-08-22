#pragma once

#include <core/base/unreachable.hpp>
#include <core/platform.hpp>

#include <string_view>

/// \def MORPHEUS_BREAKPOINT
///     Inserts a breakpoint into the code.
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <intrin.h>
    #define MORPHEUS_BREAKPOINT() do { __debugbreak(); MORPHEUS_UNREACHABLE; } while (0)
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)
    #include <signal.h>
    #define MORPHEUS_BREAKPOINT() do { raise(SIGTRAP); MORPHEUS_UNREACHABLE; } while (0)
#else
    #define MORPHEUS_BREAKPOINT() do { *(int*)0 = 0; MORPHEUS_UNREACHABLE; } while(0)
#endif

namespace morpheus
{

/// Prints debug messages to any approptiate error channels.
/// \param[im] message 
///     The error message to display.
void debugPring(std::string_view message);

}