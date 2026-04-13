#pragma once

#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/platform/monitor.hpp>

namespace morpheus::gfx::win32
{

concurrency::Generator<Monitor> enumerateMonitors() noexcept;

} // namespace morpheus::gfx::win32
