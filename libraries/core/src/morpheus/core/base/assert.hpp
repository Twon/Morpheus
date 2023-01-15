#pragma once

#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/conformance/source_location.hpp>

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>

namespace morpheus 
{

/// \struct Assertion
///     Minium required information to report an assetion.
struct Assertion
{
    sl_ns::source_location location; ///< The location of the assertion.
    std::string_view expression; ///< The expression which resulted in the assertion.
    std::string message; ///< Message with human readable decription of the assertion.
};
    
/// \typedef AssertHandler
///     Callback that defines custom behaviour when an assert is hit.
using AssertHandler = std::function<bool(Assertion)>;

/// Set a custom global assert handler.
/// \param[in] handler
///     A custom assert handler to override existing handling behaviour with.
MORPHEUSCORE_EXPORT void setAssertHandler(AssertHandler handler);

/// Access the globally enable assert handler.
[[nodiscard]] MORPHEUSCORE_EXPORT AssertHandler const& getAssertHandler();

/// \enum AssertType
///     Defines the behavour type for assert handlers.
enum class MORPHEUSCORE_EXPORT AssertType
{
    Assert, /// Assert behavour calls the handler and calls halt if the handler returns true.
    Verify  /// Verify behavour calls the handler and unconditionally calls halt.
};

/// Triggers the global assert handler. 
/// \param[in] type The type of assert behavour.
/// \param[in] location The source file location where the assert orginated.
/// \param[in] expr String representation of the condition.
/// \param[in] message An optional message describing the assert.
MORPHEUSCORE_EXPORT void assertHandler(AssertType type, sl_ns::source_location const location, std::string_view const expr, std::string_view message = std::string_view());


/// \def MORPHEUS_ASSERT_ENABLED
///     Test macro which is enabled by default for debug builds.
/// \note 
///     This can be manually disabled by defining MORPHEUS_DISABLE_ASSERT.  This allows for removing
///     asserts in debug builds.
#if !defined(NDEBUG) && !defined(MORPHEUS_ASSERT_ENABLED) && !defined(MORPHEUS_DISABLE_ASSERT)
#define MORPHEUS_ASSERT_ENABLED
#endif


#if defined (MORPHEUS_ASSERT_ENABLED)
    #define MORPHEUS_ASSERT_HANDLER(type, expr, msg) \
        do \
            if ((!static_cast<bool>(expr))) [[unlikely]] \
                assertHandler(type, MORPHEUS_CURRENT_LOCATION, #expr, msg); \
        while(0)

#else
    #define MORPHEUS_ASSERT_HANDLER(type, expr, msg)
#endif


#define MORPHEUS_ASSERT(expr) \
    MORPHEUS_ASSERT_HANDLER(::morpheus::AssertType::Assert, expr, {})

#define MORPHEUS_ASSERT_MSG(expr, msg) \
    MORPHEUS_ASSERT_HANDLER(::morpheus::AssertType::Assert, expr, (msg))

}