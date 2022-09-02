#pragma once

#include <core/base/platform.hpp>

#include <GL/glew.h>

#if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/wglew.h>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
#include <OpenGL/gl.h>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)
#include <GL/gl.h>
#endif //#if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)


