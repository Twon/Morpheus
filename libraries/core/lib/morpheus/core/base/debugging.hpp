#pragma once

#include <morpheus/core/base/export.hpp>

#include <string_view>

namespace morpheus
{
/// \def MORPHEUS_DEBUG_ENABLED
///     Test macro which is enabled by default for debug builds.  This may be define by users when
///     it is known that debug behaviour is intended. Conversely it can be disabled by defining
///     MORPHEUS_DISABLE_DEBUG
/// \note
///     This can be manually disabled by defining MORPHEUS_DISABLE_DEBUG.  This allows for removing
///     asserts in debug builds.
#if !defined(NDEBUG) && !defined(MORPHEUS_DEBUG_ENABLED) && !defined(MORPHEUS_DISABLE_DEBUG)
    #define MORPHEUS_DEBUG_ENABLED
#endif

/// Inserts a breakpoint into the code.
/// \note
///     Models std::breakpoint as per:
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2514r0.html
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2546r1.html
/// \note
///     Implementations:
///     - https://github.com/grafikrobot/debugging
///     - https://github.com/scottt/debugbreak
///     - https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
///     - https://github.com/bruxisma/breakpoint
MORPHEUSCORE_EXPORT void breakpoint() noexcept;

/// Inserts a breakpoint into the code when the process is under a debugger.
/// \note
///     Models std::breakpoint_if_debugging as per:
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2546r1.html
MORPHEUSCORE_EXPORT void breakpoint_if_debugging() noexcept;

/// Detects if a process is debugging the process.
/// \note
///     Models std::is_debugger_present as per:
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2546r1.html
MORPHEUSCORE_EXPORT bool is_debugger_present() noexcept;

/// Prints debug messages to any approptiate error channels.
/// \param[in] message
///     The error message to display.
MORPHEUSCORE_EXPORT void debugPrint(std::string_view const message);

} // namespace morpheus
