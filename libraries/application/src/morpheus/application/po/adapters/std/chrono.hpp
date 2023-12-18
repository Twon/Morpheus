#pragma once

#include "morpheus/core/conversion/adapters/std/chrono.hpp"

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include <chrono>
#include <string>
#include <vector>

namespace boost
{

template <class CharType, class Rep, class Period>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, std::chrono::duration<Rep, Period>*, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    auto const duration = morpheus::conversion::fromString<std::chrono::duration<Rep, Period>>(s);
    if (duration)
        v = duration.value();
    else
        throw po::validation_error(po::validation_error::invalid_option_value);
}

} // namespace boost
