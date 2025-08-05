#pragma once

//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#endif // #if (MORPHEUS_MODULES_SUPPORT)

#include <morpheus/core/base/export.hpp>
#include <morpheus/core/conformance/source_location.hpp>

//#if (!MORPHEUS_MODULES_SUPPORT)
    #include <functional>
    #include <string_view>
//#endif // #if (!MORPHEUS_MODULES_SUPPORT)

namespace morpheus
{

/// \struct Assertion
///     Minimum required information to report an assetion.
struct Assertion
{
    sl_ns::source_location location; ///< The location of the assertion.
    std::string_view expression;     ///< The expression which resulted in the assertion.
    std::string_view message;        ///< Message with human readable description of the assertion.
};

/// Callback that defines custom behaviour when an assert is hit.
using AssertHandler = std::function<bool(Assertion)>;

/// Set a custom global assert handler.
/// \param[in] handler
///     A custom assert handler to override existing handling behaviour with.
/// \return
///     The previous assert handler.
MORPHEUSCORE_EXPORT AssertHandler setAssertHandler(AssertHandler handler);

/// Access the globally enable assert handler.
[[nodiscard]] MORPHEUSCORE_EXPORT AssertHandler const& getAssertHandler();

/// Callback that defines custom behaviour when an assert must halt the program.
using AssertHaltHandler = std::function<void()>;

/// Set a custom global assert halt handler.
/// \param[in] handler
///     A custom assert halt handler to customise assert halting behaviour.
/// \return
///     The previous assert halt handler.
MORPHEUSCORE_EXPORT AssertHaltHandler setAssertHaltHandler(AssertHaltHandler handler);

/// Access the globally enable assert halt handler.
[[nodiscard]] MORPHEUSCORE_EXPORT AssertHaltHandler const& getAssertHaltHandler();

/// \enum AssertType
///     Defines the behaviour type for assert handlers.
enum class MORPHEUSCORE_EXPORT AssertType
{
    Assert, ///< Assert behaviour calls the handler and calls halt if the handler returns true.
    Verify  ///< Verify behaviour calls the handler and unconditionally calls halt.
};

/// Triggers the global assert handler.
/// \param[in] type The type of assert behaviour.
/// \param[in] location The source file location where the assert originated.
/// \param[in] expr String representation of the condition.
/// \param[in] message An optional message describing the assert.
MORPHEUSCORE_EXPORT void assertHandler(AssertType type, sl_ns::source_location const location, std::string_view const expr,
                                       std::string_view message = std::string_view());



} // namespace morpheus
