#pragma once

namespace morpheus
{

/// Ensure that asserts fired in morpheus code is captured and reported through Catch2's error reporting.
void enableCatch2AssertHooks();

} // namespace morpheus