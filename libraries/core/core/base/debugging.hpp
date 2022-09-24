#pragma once

#include <core/base/platform.hpp>
#include <core/base/unreachable.hpp>

#include <string_view>

/// \def MORPHEUS_BREAKPOINT
///     Inserts a breakpoint into the code.
/// \note
///     Models std::breakpoint: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2514r0.html
/// \note
///     Implementations:
///     - https://github.com/grafikrobot/debugging
///     - https://github.com/scottt/debugbreak
///     - https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <intrin.h>
    #define MORPHEUS_BREAKPOINT() do { __debugbreak(); MORPHEUS_UNREACHABLE; } while (0)
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX) || \
      (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <signal.h>
    #define MORPHEUS_BREAKPOINT() do { raise(SIGTRAP); MORPHEUS_UNREACHABLE; } while (0)
#else
    #define MORPHEUS_BREAKPOINT() //do { *(int*)0 = 0; MORPHEUS_UNREACHABLE; } while(0)
#endif

namespace morpheus
{

/// Prints debug messages to any approptiate error channels.
/// \param[im] message 
///     The error message to display.
void debugPring(std::string_view message);

}