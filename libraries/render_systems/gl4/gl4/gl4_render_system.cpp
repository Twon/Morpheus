#include <gl4/gl4_render_system.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)

#include <OpenGL/gl.h>

namespace morpheus::gfx::gl4
{

//---------------------------------------------------------------------------------------------------------------------

render_system::~render_system()
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::gl4
