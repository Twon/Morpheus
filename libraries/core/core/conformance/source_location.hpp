#pragma once

#if __has_include(<source_location>)

#include <source_location>
namespace morpheus { namespace sl_ns = std; }

#define MORPHEUS_CURRENT_LOCATION sl_ns::source_location::current()

#else

#include<boost/assert/source_location.hpp>
namespace morpheus { namespace sl_ns = fmt; }

#define MORPHEUS_CURRENT_LOCATION BOOST_CURRENT_LOCATION

#endif
