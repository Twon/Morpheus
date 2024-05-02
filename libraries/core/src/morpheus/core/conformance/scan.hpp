#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<scan>)
    #include <scan>
#endif

// clang-format off
#include <scn/scan.h>
namespace morpheus { namespace scan_ns = scn; }

// clang-format on
