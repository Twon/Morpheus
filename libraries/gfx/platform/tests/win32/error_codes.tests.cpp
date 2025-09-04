#include "morpheus/gfx/platform/win32/error_codes.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp> // for GENERATE

#include <array>
#include <string>
#include <string_view>
#include <system_error>

namespace morpheus::gfx::win32
{

TEST_CASE("Test construction of std::error_code for win32 errors via make_error_code", "[morpheus.gfx.win32.error_code.make_error_code]")
{
    DWORD const win32ErrorCode = GENERATE(ERROR_SUCCESS,
                                          ERROR_FILE_NOT_FOUND,
                                          ERROR_PATH_NOT_FOUND,
                                          ERROR_ACCESS_DENIED,
                                          ERROR_INVALID_PARAMETER,
                                          ERROR_ALREADY_EXISTS,
                                          ERROR_BUFFER_OVERFLOW,
                                          ERROR_NOT_SUPPORTED,
                                          ERROR_OUTOFMEMORY,
                                          ERROR_HANDLE_EOF);
    std::error_code error_code = make_error_code(ErrorCode(win32ErrorCode));
    REQUIRE(error_code.value() == static_cast<int>(win32ErrorCode));
    REQUIRE(std::string_view(error_code.category().name()) == std::string_view("Win32::ErrorCategory"));
    REQUIRE(error_code.message() != "unknown");
}

TEST_CASE("Test construction of std::error_code for win32 errors via make_error_code", "[morpheus.gfx.win32.error_code.make_win32_error_code]")
{
    SetLastError(ERROR_SUCCESS);
    std::error_code error_code = getLastErrorCode();
    REQUIRE(error_code.value() == static_cast<int>(ERROR_SUCCESS));
    REQUIRE(std::string_view(error_code.category().name()) == std::string_view("Win32::ErrorCategory"));
    REQUIRE(error_code.message() != "Success");
}

} // namespace morpheus::gfx::win32
