#pragma once

#include <morpheus/core/base/prerequisites.hpp>

#include <system_error>

namespace morpheus::gfx::win32
{

struct [[nodiscard]] ErrorCode
{
    constexpr explicit ErrorCode(DWORD const e) noexcept
        : error(e)
    {}
    DWORD error;
};

} // namespace morpheus::gfx::win32

namespace std
{
template <>
struct is_error_code_enum<morpheus::gfx::win32::ErrorCode> : true_type
{};
} // namespace std

namespace morpheus::gfx::win32
{

namespace details
{
class ErrorCategory;
}

/// Retrieve the one instance of the Win32 error category
/// \return The one instance of the Win32 error category.
details::ErrorCategory const& ErrorCategory() noexcept;

} // namespace morpheus::gfx::win32

/// Overload the global make_error_code() free function with a ErrorCode. It will be found via ADL by the compiler if needed.
/// \param[in] error The error raised by the underlying Win32 API.
/// \return A std::error_code with Win32 error encoded into it.
/// \note Becasue windows error codes are just DWORD values, and thus not strongly typed, you must explicitly wrap them in an ErrorCode constructed from a
///       DWORD to pass to the make_error_code overload or call the helper overload getLastErrorCode() which initialised an error code from GetLastError().
/// \code
///     std::error_code ec = make_error_code(morpheus::gfx::win32::ErrorCode{ERROR_FILE_NOT_FOUND});
/// \endcode
std::error_code make_error_code(morpheus::gfx::win32::ErrorCode const& e);

/// Overload the getLastErrorCode which is initialised from GetLastError().
/// \param[in] error The error raised by the underlying Win32 API.
/// \return A std::error_code with Win32 error encoded into it.
std::error_code getLastErrorCode();
