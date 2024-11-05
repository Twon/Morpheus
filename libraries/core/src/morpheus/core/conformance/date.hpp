#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<chrono>)
    #include <chrono> // IWYU pragma: export
#endif

// clang-format off
#if (__cpp_lib_chrono >= 201907L )
    namespace morpheus { namespace date_ns = std::chrono; }
#else
    #include <date/date.h> // IWYU pragma: export
    #include <date/tz.h> // IWYU pragma: export
    namespace morpheus { namespace date_ns = date; }
#endif
// clang-format on
