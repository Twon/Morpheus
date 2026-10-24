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

auto breakpoint_if_debugging() noexcept -> void
{
    if (is_debugger_present())
    {
        breakpoint();
    }
}

auto is_debugger_present() noexcept -> bool
{
    return boost::debug::under_debugger(); // LCOV_EXCL_LINE
}

auto debugPrint(std::string_view const message) -> void
{
    std::cerr << message;
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    OutputDebugString(message.data());
#endif
}

} // namespace morpheus
