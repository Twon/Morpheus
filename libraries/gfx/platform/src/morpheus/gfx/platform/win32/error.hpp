#pragma once

#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/monitor.hpp>

#include <string>

namespace morpheus::gfx::win32
{

std::wstring GetLastErrorWString(DWORD errorCode);

std::string GetLastErrorString(DWORD errorCode);

std::string WStringToString(std::wstring const& wstr);

} // namespace morpheus::gfx::win32
