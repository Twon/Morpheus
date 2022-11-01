#pragma once

#include <morpheus/gfx/platform/adapter.hpp>

#include <morpheus/core/concurrency/generator.hpp>

namespace morpheus::gfx::nvidia::nvapi
{

/// \using Adapter
///  
/// 
using Adapter = gfx::Adapter<std::uint32_t>;

concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::nvidia::nvapi
