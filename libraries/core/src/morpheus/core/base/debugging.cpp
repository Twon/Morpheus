#include "morpheus/core/base/debugging.hpp"
#include "morpheus/core/base/platform.hpp"
#include "morpheus/core/base/prerequisites.hpp"

#include <boost/test/debug.hpp>

#include <iostream>

namespace morpheus
{

void breakpoint() noexcept
{
#if defined(MORPHEUS_DEBUG_ENABLED)
    boost::debug::debugger_break();
#else
    debugPrint("Breakpoint hit but currently disabled (See MORPHEUS_DEBUG_ENABLED for details).");
#endif
}

void breakpoint_if_debugging() noexcept
{
    if (is_debugger_present())
        breakpoint();
}

bool is_debugger_present() noexcept
{
    return boost::debug::under_debugger();
}

void debugPrint(std::string_view const message)
{
    std::cerr << message;
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    OutputDebugString(message.data());
#endif
}

} // namespace morpheus
