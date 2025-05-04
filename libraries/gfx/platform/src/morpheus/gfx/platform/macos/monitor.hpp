#pragma once

#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/platform/monitor.hpp>

namespace morpheus::gfx::macos
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept;

} // namespace morpheus::gfx::macos
