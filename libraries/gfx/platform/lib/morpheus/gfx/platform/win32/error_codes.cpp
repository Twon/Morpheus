#include <morpheus/gfx/platform/win32/error.hpp>
#include <morpheus/gfx/platform/win32/error_codes.hpp>

#include <string>

namespace morpheus::gfx::win32
{

namespace details
{
/*! \class vulkan_error_category
        Defines an error code category for Vulkan return codes to plug them into the std::error_code framework.
 */
class ErrorCategory : public std::error_category
{
public:
    /*! Queries a short form descriptive name for the category.
        \return Short form name of the category.
     */
    char const* name() const noexcept override final { return "Win32::ErrorCategory"; }

    /*! Queries an error string describing the error.
        \return The error message.
     */
    std::string message(int c) const override final { return GetLastErrorString(static_cast<DWORD>(c)); }

    static ErrorCategory const& getSingleInstance() noexcept { return mSingleInstance; }

private:
    static ErrorCategory mSingleInstance;
};

ErrorCategory ErrorCategory::mSingleInstance;

} // namespace details

details::ErrorCategory const& ErrorCategory() noexcept
{
    return details::ErrorCategory::getSingleInstance();
}

} // namespace morpheus::gfx::win32

std::error_code make_error_code(morpheus::gfx::win32::ErrorCode const& e)
{
    return std::error_code(static_cast<int>(e.error), morpheus::gfx::win32::ErrorCategory());
}

std::error_code getLastErrorCode()
{
    return make_error_code(morpheus::gfx::win32::ErrorCode{::GetLastError()});
}
