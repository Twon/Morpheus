#pragma once

#include <morpheus/core/base/platform.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include <GL/glew.h>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <GL/wglew.h>
    #include <windows.h>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <OpenGL/gl.h>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_LINUX)
    #include <GL/gl.h>
#else
    #error "Unsupported platform for GL render system."
#endif // #if (MORPHEUS_BUILD_PLATFORM==MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
