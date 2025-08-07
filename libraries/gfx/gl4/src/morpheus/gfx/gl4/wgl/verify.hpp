#pragma once

#include <morpheus/core/base/verify.hpp>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdexcept>
#include <system_error>

namespace morpheus::gfx::gl4::wgl
{

/// Get the message containing the error string for GetLastError().
/// \note
///     https://stackoverflow.com/a/62070624/4764531
inline std::string getLastErrorMessage()
{
    DWORD const error = ::GetLastError();
    return std::system_category().message(error);
}

/// \def MORPHEUS_WGL_VERIFY
///
///
#define MORPHEUS_WGL_VERIFY(expr) MORPHEUS_VERIFY_MSG(expr, getLastErrorMessage())

} // namespace morpheus::gfx::gl4::wgl
