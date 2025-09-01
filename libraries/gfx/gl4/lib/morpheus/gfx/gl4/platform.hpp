#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/gfx/gl4/prerequisites.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

// clang-format off
#include <morpheus/gfx/gl4/wgl/adapter.hpp>
#include <morpheus/gfx/gl4/wgl/context.hpp>
#include <morpheus/gfx/gl4/wgl/video_mode.hpp>
#include <morpheus/gfx/gl4/wgl/window.hpp>
// clang-format on

namespace platform = morpheus::gfx::gl4::wgl;

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

/// \todo
///     Delete me once I really exist and am accessed via a header.
namespace morpheus::gfx::gl4::agl
{}

namespace platform = morpheus::gfx::gl4::agl;

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)

// clang-format off
#include <morpheus/gfx/gl4/xgl/context.hpp>
// clang-format on

namespace platform = morpheus::gfx::gl4::xgl;

#endif
