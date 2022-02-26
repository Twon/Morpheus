#pragma once

#if __has_include(<format>)
#include <format>
#endif

#if !(__cpp_lib_format >= 201907L)

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace morpheus
{
    using namespace fmt;
} // namespace morpheus

#endif
