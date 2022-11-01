#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/platform/adapter.hpp>

#include <string>

namespace morpheus::gfx::intel::win32
{

/// \using Adapter
///  
/// 
using Adapter = gfx::Adapter<std::uint32_t>;

concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::intel::win32
