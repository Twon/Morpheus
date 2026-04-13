#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/gl4/wgl/adapter.hpp>
#include <morpheus/gfx/platform/video_mode.hpp>

namespace morpheus::gfx::gl4::wgl
{

using VideoMode = gfx::VideoMode;

concurrency::Generator<VideoMode> enumerateVideoModes(Adapter const& adapter);

} // namespace morpheus::gfx::gl4::wgl
