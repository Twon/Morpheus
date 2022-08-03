#pragma once

#include <core/concurrency/generator.hpp>
#include <core/gfx/adapters/adapter.hpp>
#include <core/platform.hpp>

#include <string>

namespace morpheus::gfx::gl4::wgl
{

/// \using Adapter
///  
/// 
using Adapter = gfx::Adapter<std::string>;


concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::gl4::wgl
