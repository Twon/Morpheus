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
    std::string_view expression;     ///< The expression which resulted in the assertion.
    std::string_view message;        ///< Message with human readable decription of the assertion.
};

/// \using AssertHandler
///     Callback that defines custom behaviour when an assert is hit.
using AssertHandler = std::function<bool(Assertion)>;

/// Set a custom global assert handler.
/// \param[in] handler
///     A custom assert handler to override existing handling behaviour with.
/// \return
///     The previous assert handler.
MORPHEUSCORE_EXPORT AssertHandler setAssertHandler(AssertHandler handler);

/// Access the globally enable assert handler.
[[nodiscard]] MORPHEUSCORE_EXPORT AssertHandler const& getAssertHandler();

/// \using AssertHaltHandler
///     Callback that defines custom behaviour when an assert must halt the program.
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
///     Defines the behavour type for assert handlers.
enum class MORPHEUSCORE_EXPORT AssertType
{
    Assert, ///< Assert behavour calls the handler and calls halt if the handler returns true.
    Verify  ///< Verify behavour calls the handler and unconditionally calls halt.
};

/// Triggers the global assert handler.
/// \param[in] type The type of assert behavour.
/// \param[in] location The source file location where the assert orginated.
/// \param[in] expr String representation of the condition.
/// \param[in] message An optional message describing the assert.
MORPHEUSCORE_EXPORT void assertHandler(AssertType type, sl_ns::source_location const location, std::string_view const expr,
                                       std::string_view message = std::string_view());



} // namespace morpheus
