#include "morpheus/core/base/debugging.hpp"
#include "morpheus/core/base/prerequisites.hpp"

#include <boost/test/debug.hpp>

// clang-format off
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <debugapi.h> // Windows.h must be included before this (current via prerequisites).
    #include <intrin.h>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX) ||                                                   \
      (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <signal.h>
#endif
// clang-format on

#include <cstdio>
#include <iostream>

namespace morpheus
{

void breakpoint() noexcept
{

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    __debugbreak();
    unreachable();
// https://github.com/scottt/debugbreak/issues/24
#elif (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER) && defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
    __builtin_debugtrap();
    unreachable();
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX) || (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    raise(SIGTRAP);
    unreachable();
#else
    // *(int*)0 = 0;
    // unreachable();
#endif
}

void breakpoint_if_debugging() noexcept
{
#if defined(MORPHEUS_DEBUG_ENABLED)
    if (is_debugger_present())
        breakpoint();
#else
    debugPrint("Breakpoint hit but currently disabled (See MORPHEUS_DEBUG_ENABLED for details).");
#endif
}

bool is_debugger_present() noexcept { return boost::debug::under_debugger(); }

void debugPrint(std::string_view const message)
{
    std::cerr << message;
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    OutputDebugString(message.data());
#endif
}

} // namespace morpheus