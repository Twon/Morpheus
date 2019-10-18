#include <gl4/gl4_render_system.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


namespace morpheus::gfx::gl4
{

//---------------------------------------------------------------------------------------------------------------------

render_system::~render_system()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::gl4
