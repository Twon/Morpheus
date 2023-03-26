#include "morpheus/core/base/debugging.hpp"
#include "morpheus/core/base/prerequisites.hpp"
#include "morpheus/core/conformance/print.hpp"

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

namespace morpheus
{

void breakpoint() noexcept
{

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    __debugbreak();
    MORPHEUS_UNREACHABLE;
// https://github.com/scottt/debugbreak/issues/24
#elif (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER) && defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
    __builtin_debugtrap();
    MORPHEUS_UNREACHABLE;
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX) ||                                                   \
    (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    raise(SIGTRAP);
    MORPHEUS_UNREACHABLE;
#else
    // *(int*)0 = 0;
    // MORPHEUS_UNREACHABLE;
#endif
}

void breakpoint_if_debugging() noexcept
{
#if defined (MORPHEUS_DEBUG_ENABLED)
    if (is_debugger_present())
        breakpoint();
#else
    debugPrint("Breakpoint hit but currently disabled (See MORPHEUS_DEBUG_ENABLED for details).");
#endif
}

bool is_debugger_present() noexcept { return boost::debug::under_debugger(); }

void debugPrint(std::string_view const message)
{
    print_ns::print(stderr, "{}", message);
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    OutputDebugString(message.data());
#endif
}

} // namespace morpheus