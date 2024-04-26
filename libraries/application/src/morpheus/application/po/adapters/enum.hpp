#pragma once

#include "morpheus/core/meta/concepts/enum.hpp"
#include "morpheus/core/conversion/adapters/enum.hpp"

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <vector>

namespace boost
{

template <class CharType, morpheus::meta::concepts::Enum E>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, E*, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    auto const result = morpheus::conversion::fromString<E>(s);
    if (result)
        v = result.value();
    else
        throw po::validation_error(po::validation_error::invalid_option_value);
}

} // namespace boost
