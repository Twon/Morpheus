#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/core/conformance/expected.hpp>

#include <string>

namespace morpheus::gfx::win32
{
std::wstring GetLastErrorWString(DWORD errorCode);
std::string GetLastErrorString(DWORD errorCode);

std::string WStringToString(std::wstring const& wstr);

template <typename T>
auto makeExpected(T&& value)
{
    return conf::exp::expected<std::decay_t<T>, std::string>{std::forward<T>(value)};
}

inline auto makeUnexpected()
{
    return conf::exp::unexpected(GetLastErrorString(GetLastError()));
}

} // namespace morpheus::gfx::win32
