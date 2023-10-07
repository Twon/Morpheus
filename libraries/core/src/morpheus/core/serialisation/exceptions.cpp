#include "morpheus/core/base/exceptions.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <boost/exception/all.hpp>

namespace morpheus::serialisation
{

void throwBinaryException(std::string_view message)
{
    throw boost::enable_error_info(BinaryException(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

void throwJsonException(std::string_view message)
{
    throw boost::enable_error_info(JsonException(std::string(message))) << ExceptionInfo(MORPHEUS_CURRENT_STACKTRACE);
}

} // namespace morpheus::serialisation
