#include <core/base/debugging.hpp>
#include <core/conformance/print.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <debugapi.h>
#endif

#include <cstdio>

namespace morpheus
{

    void debugPring(std::string_view const message)
    {
        print_ns::print(stderr, "{}", message);
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
        OutputDebugString(message.data());
#endif
    }

}