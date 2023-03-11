#pragma once

#if __has_include(<stacktrace>)
#include <stacktrace>
#endif

#if (__cpp_lib_stacktrace >= 202011L)

namespace morpheus { namespace st_ns = std; }

#else

#include <boost/stacktrace/stacktrace.hpp
namespace morpheus { namespace st_ns = boost; }

#endif
