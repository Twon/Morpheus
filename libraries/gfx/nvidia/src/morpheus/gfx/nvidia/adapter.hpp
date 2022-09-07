#pragma once

#include <core/concurrency/generator.hpp>
#include <core/gfx/adapter.hpp>

namespace morpheus::gfx::nvidia::nvapi
{

/// \using Adapter
///  
/// 
using Adapter = gfx::Adapter<std::uint32_t>;

concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::nvidia::nvapi
