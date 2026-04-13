#pragma once

#include <morpheus/core/conformance/version.hpp>

#if __has_include(<scan>)
    #include <scan> // IWYU pragma: export
#endif

// clang-format off
#include <utility>
#include <scn/scan.h> // IWYU pragma: export
namespace morpheus::conf { namespace scan = ::scn; }

// clang-format on
