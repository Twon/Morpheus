#pragma once

#include <boost/log/core.hpp>

namespace morpheus
{

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