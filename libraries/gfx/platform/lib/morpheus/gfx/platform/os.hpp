#pragma once

#include "morpheus/core/base/platform.hpp"

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

// clang-format off
#include "morpheus/gfx/platform/win32/monitor.hpp"
#include "morpheus/gfx/platform/win32/render_window.hpp"
// clang-format on

namespace morpheus::gfx
{

namespace os = win32;

} // namespace morpheus::gfx

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

// clang-format off
#include "morpheus/gfx/platform/macos/monitor.hpp"
#include "morpheus/gfx/platform/macos/render_window.hpp"
// clang-format on

namespace morpheus::gfx
{

namespace os = macos;

} // namespace morpheus::gfx

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)

// clang-format off
#include "morpheus/gfx/platform/x11/monitor.hpp"
#include "morpheus/gfx/platform/x11/render_window.hpp"
// clang-format on

namespace morpheus::gfx
{

namespace os = x11;

} // namespace morpheus::gfx

#endif // #if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
