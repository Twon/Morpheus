#pragma once

#include <morpheus/core/base/assert_handler.hpp>
#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/base/verify.hpp>
#include <morpheus/core/conformance/source_location.hpp>

//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#else
    #include <cstdint>
    #include <functional>
    #include <string>
    #include <string_view>
//#endif // #if (MORPHEUS_MODULES_SUPPORT)

namespace morpheus
{

/// \def MORPHEUS_ASSERT_ENABLED
///     Test macro which is enabled by default for debug builds.
/// \note
///     This can be manually disabled by defining MORPHEUS_DISABLE_ASSERT.  This allows for removing
///     asserts in debug builds.
#if !defined(NDEBUG) && !defined(MORPHEUS_ASSERT_ENABLED) && !defined(MORPHEUS_DISABLE_ASSERT)
    #define MORPHEUS_ASSERT_ENABLED
#endif


#if defined(MORPHEUS_ASSERT_ENABLED)
    #define MORPHEUS_ASSERT_HANDLER(type, expr, msg) MORPHEUS_VERIFY_HANDLER(type, expr, msg)
#else
    #define MORPHEUS_ASSERT_HANDLER(type, expr, msg) ((void)0)
#endif

#define MORPHEUS_ASSERT(expr) MORPHEUS_ASSERT_HANDLER(::morpheus::AssertType::Assert, expr, {})

#define MORPHEUS_ASSERT_MSG(expr, msg) MORPHEUS_ASSERT_HANDLER(::morpheus::AssertType::Assert, expr, (msg))

} // namespace morpheus
