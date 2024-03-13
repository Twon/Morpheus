#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/platform/adapter.hpp>

#include <string>

namespace morpheus::gfx::gl4::wgl
{

/// \typedef Adapter
///
///
using Adapter = gfx::Adapter<std::string>;


concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::gl4::wgl
