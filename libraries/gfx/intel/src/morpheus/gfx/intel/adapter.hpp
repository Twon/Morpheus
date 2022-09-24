#pragma once

#include <core/base/platform.hpp>
#include <core/concurrency/generator.hpp>
#include <core/gfx/adapter.hpp>

#include <string>

namespace morpheus::gfx::intel::win32
{

/// \using Adapter
///  
/// 
using Adapter = gfx::Adapter<std::uint32_t>;

concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::intel::win32
