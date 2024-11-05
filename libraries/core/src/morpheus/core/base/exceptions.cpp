#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/core/conformance/stacktrace.hpp>

#include <boost/exception/exception.hpp>

#include <stdexcept>
#include <string>

namespace morpheus
{

void throwRuntimeException(std::string_view message)
{
    throw boost::enable_error_info(std::runtime_error(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

} // namespace morpheus
