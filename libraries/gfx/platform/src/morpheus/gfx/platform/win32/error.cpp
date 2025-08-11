
#include <morpheus/core/base/prerequisites.hpp>
#include <morpheus/gfx/platform/win32/error.hpp>

namespace morpheus::gfx::win32
{

std::wstring GetLastErrorWString(DWORD errorCode)
{
    LPWSTR messageBuffer = nullptr;

    DWORD size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorCode,
                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, nullptr);

    std::wstring message = (size && messageBuffer) ? messageBuffer : L"Unknown error";
    if (messageBuffer)
    {
        LocalFree(messageBuffer);
    }
    return message;
}

std::string GetLastErrorString(DWORD errorCode)
{
    std::wstring error = GetLastErrorWString(errorCode);
    return WStringToString(error);
}

std::string WStringToString(std::wstring const& wstr)
{
    if (wstr.empty())
        return {};

    int sizeNeeded = WideCharToMultiByte(CP_UTF8,                                   // Code page for UTF-8
                                         0,                                         // Flags
                                         wstr.data(),                               // Input
                                         static_cast<int>(wstr.size()), nullptr, 0, // Output buffer and size
                                         nullptr, nullptr);                         // Default char and used flag

    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), str.data(), sizeNeeded, nullptr, nullptr);
    return str;
}

} // namespace morpheus::gfx::win32
