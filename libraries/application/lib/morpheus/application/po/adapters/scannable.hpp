#pragma once

#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/meta/concepts/scannable.hpp"

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <vector>

namespace boost
{

template <class CharType, typename S>
requires morpheus::meta::concepts::Scannable<S, CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, S*, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    auto const result = morpheus::conf::scan::scan<S>(s, "{}");
    if (result)
        v = result.value().value();
    else
        throw po::validation_error(po::validation_error::invalid_option_value);
}

} // namespace boost
