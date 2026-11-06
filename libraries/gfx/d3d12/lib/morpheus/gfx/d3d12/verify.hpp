#pragma once

#include <morpheus/gfx/d3d12/prerequisites.hpp>

#include <libassert/assert.hpp>

namespace morpheus::gfx::d3d12
{

/// Get the message containing the error string for GetLastError().
/// \note
///     https://stackoverflow.com/a/62070624/4764531
inline std::string getLastErrorMessage()
{
    DWORD const error = ::GetLastError();
    return std::system_category().message(error);
}

/// \def MORPHEUS_D3D12_VERIFY
///
///
#define MORPHEUS_D3D12_VERIFY(expr)                    \
    do                                                 \
    {                                                  \
        HRESULT const hr = expr;                       \
        ASSERT(FAILED(hr), getLastErrorMessage(), hr); \
    }                                                  \
    while (0)

} // namespace morpheus::gfx::d3d12
