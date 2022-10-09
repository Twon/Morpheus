#pragma once

#include <core/base/compiler.hpp>
#include <core/base/platform.hpp>
#include <core/base/unreachable.hpp>

#include <string_view>

namespace morpheus
{

/// Inserts a breakpoint into the code.
/// \note
///     Models std::breakpoint: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2514r0.html
/// \note
///     Implementations:
///     - https://github.com/grafikrobot/debugging
///     - https://github.com/scottt/debugbreak
///     - https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
///     - https://github.com/bruxisma/breakpoint
void breakpoint() noexcept;

/// \function breakpoint
///
bool isDebuggerAttached();

/// Prints debug messages to any approptiate error channels.
/// \param[im] message 
///     The error message to display.
void debugPring(std::string_view const message);

}