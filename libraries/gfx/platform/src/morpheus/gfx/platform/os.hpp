#pragma once

#include "morpheus/core/base/platform.hpp"

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

#include "morpheus/gfx/platform/win32/monitor.hpp"
#include "morpheus/gfx/platform/win32/render_window.hpp"

namespace morpheus::gfx
{

namespace os = macos;

} // namespace morpheus::gfx

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

#include "morpheus/gfx/platform/macos/monitor.hpp"
#include "morpheus/gfx/platform/macos/render_window.hpp"

namespace morpheus::gfx
{

namespace os = macos;

} // namespace morpheus::gfx

#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)

#include "morpheus/gfx/platform/x11/monitor.hpp"
#include "morpheus/gfx/platform/x11/render_window.hpp"

namespace morpheus::gfx
{

namespace os = x11;

} // namespace morpheus::gfx

#endif // #if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
