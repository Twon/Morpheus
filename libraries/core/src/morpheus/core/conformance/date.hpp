#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<chrono>)
    #include <chrono>
#endif

// clang-format off
#if (__cpp_lib_chrono >= 201907L )
    namespace morpheus { namespace date_ns = std::chrono; }
#else
    #include <date/date.h>
    #include <date/tz.h>
    namespace morpheus { namespace date_ns = date; }
#endif
// clang-format on
