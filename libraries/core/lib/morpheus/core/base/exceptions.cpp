#include <morpheus/core/base/exceptions.hpp>
#include <morpheus/core/conformance/stacktrace.hpp>

#include <boost/exception/exception.hpp>

#include <stdexcept>
#include <string>

namespace morpheus
{

void throwRuntimeException(std::string_view message)
{
    // Boost.Exception wraps std::runtime_error to attach diagnostic information.
    // NOLINTNEXTLINE(misc-throw-by-value-catch-by-reference, cert-err09-cpp, cert-err61-cpp, bugprone-exception-copy-constructor-throws, cert-err60-cpp)
    throw boost::enable_error_info(std::runtime_error(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

} // namespace morpheus
