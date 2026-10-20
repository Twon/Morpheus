#include "morpheus/core/base/exceptions.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <boost/exception/exception.hpp>

namespace morpheus::serialisation
{

void throwBinaryException(std::string_view message)
{
    // Boost.Exception wraps std::runtime_error to attach diagnostic information.
    // NOLINTNEXTLINE(misc-throw-by-value-catch-by-reference, cert-err09-cpp, cert-err61-cpp, bugprone-exception-copy-constructor-throws, cert-err60-cpp)
    throw boost::enable_error_info(BinaryException(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

void throwJsonException(std::string_view message)
{
    // Boost.Exception wraps std::runtime_error to attach diagnostic information.
    // NOLINTNEXTLINE(misc-throw-by-value-catch-by-reference, cert-err09-cpp, cert-err61-cpp, bugprone-exception-copy-constructor-throws, cert-err60-cpp)
    throw boost::enable_error_info(JsonException(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

} // namespace morpheus::serialisation
