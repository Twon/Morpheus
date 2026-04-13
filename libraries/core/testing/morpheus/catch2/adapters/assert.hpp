#pragma once

#include <morpheus/core/base/assert_handler.hpp>

namespace morpheus
{

AssertHandler const& getPreviousHandler();

/// Ensure that asserts fired in morpheus code is captured and reported through Catch2's error reporting.
void enableCatch2AssertHooks();

} // namespace morpheus
