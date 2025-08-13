
#pragma once

#include <morpheus/core/base/cold.hpp>
#include <morpheus/core/conformance/format.hpp> // IWYU pragma: export

#include <stdexcept>
#include <string_view>

namespace morpheus::gfx::d3d12
{

/// \class Exception
///
class Exception : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/// \group Exception Helpers
///     Throwing of exceptions is moved to explicitly outlined functions to ensure code density around exception sites.
///     Additionally this allows to inform the compiler that exceptions are expected to be on the cold path to ensure
///     optimal code generation where exceptions are thrown.
/// @{
/// Throws a std::runtime_error with the attached message.
[[noreturn]] MORPHEUS_FUNCTION_COLD void throwD3D12Exception(std::string_view message);

/// Throws a std::runtime_error with the attached formatted message.
/// \param[in] fmt
///      Format string specifying message output.
/// \param[in] args
///     Arguments to be fed into the formatted message output
template <class... Args>
[[noreturn]] MORPHEUS_FUNCTION_COLD void throwD3D12Exception(fmt_ns::format_string<Args...> fmt, Args&&... args)
{
    // Defect report https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2905r2.html resolves make_format_args to only accept l-values.
    throwD3D12Exception(fmt_ns::vformat(fmt.get(), fmt_ns::make_format_args(args...)));
}
/// @}

} // namespace morpheus::gfx::d3d12
