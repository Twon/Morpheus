#pragma once

#include <morpheus/core/conformance/stacktrace.hpp>

#include <concepts>
#include <exception>

namespace morpheus::application
{

///
/// \param[in] f 
void tryCatch(std::invocable auto f)
{
    try
    {
        f();
    }
    catch (std::exception const& ex)
    {
        BOOST_LOG_TRIVIAL(error) << "Exception caught: " << ex.what() << std::endl << st_ns::stacktrace::current();
    }
    catch(...)
    {
        BOOST_LOG_TRIVIAL(error) << "Unknown exception!\n" << st_ns::stacktrace::current();
    }
}

} // namespace morpheus::application