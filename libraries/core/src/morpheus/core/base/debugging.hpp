#pragma once

#include <morpheus/core/base/compiler.hpp>
#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/base/unreachable.hpp>

#include <string_view>

namespace morpheus
{

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
void breakpoint() noexcept;

/// Inserts a breakpoint into the code when the process is under a debugger.
/// \note
///     Models std::breakpoint_if_debugging as per: 
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2546r1.html
void breakpoint_if_debugging() noexcept;

/// \function is_debugger_present
///     Detects if a process is debugging the process.
/// \note
///     Models std::is_debugger_present as per: 
///     - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2546r1.html
bool is_debugger_present() noexcept;

/// Prints debug messages to any approptiate error channels.
/// \param[im] message 
///     The error message to display.
void debugPring(std::string_view const message);

}