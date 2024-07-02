#pragma once

#include <boost/log/core.hpp>

namespace morpheus
{

/// \struct LoggingFixture
///     Testing fixture which when used as or in a specific test fixture disable logging output and re-enables it at the end of the fixture scope.
struct LoggingFixture
{
    LoggingFixture()
    {
        boost::log::core::get()->set_logging_enabled(false);
    }

    ~LoggingFixture()
    {
        boost::log::core::get()->set_logging_enabled(true);
    }
};

} // namespace morpheus
