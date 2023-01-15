#pragma once

#include <concepts>
#include <exception>

namespace morpheus::application
{

///
/// \param[in] f 
tryCatch(std::invocable auto f)
{
    try
    {
        f();
    }
    catch (std::exception const& ex)
    {

    }
    catch(...)
    {

    }
}

} // namespace morpheus::application