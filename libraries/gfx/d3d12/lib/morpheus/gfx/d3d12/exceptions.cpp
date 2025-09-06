#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/core/conformance/stacktrace.hpp>
#include <morpheus/gfx/d3d12/exceptions.hpp>

#include <boost/exception/all.hpp>

#include <exception>
#include <string>
#include <string_view>

namespace morpheus::gfx::d3d12
{

void throwD3D12Exception(std::string_view message)
{
    throw boost::enable_error_info(Exception(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

} // namespace morpheus::gfx::d3d12