
#pragma once

#include <morpheus/core/base/compiler.hpp>
#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/base/cold.hpp>

#include <string_view>

namespace morpheus
{

/// \group Exception Helpers
///     Throwing of exceptions is moved to explicitly outlined functions to ensure code density around exception sites.
///     Additionally this allows to inform the compiler that exceptions are expected to be on the cold path to ensure
///     optimal code generation where exceptions are thrown.
/// @{
/// Throws a std::runtime_error with the attached message.
[[noreturn]] MORPHEUS_FUNCTION_COLD void throwRuntimeException(std::string_view message);
/// @}

} // namespace morpheus
