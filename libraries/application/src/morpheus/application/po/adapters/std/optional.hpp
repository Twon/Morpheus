#pragma once

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include <optional>
#include <string>
#include <vector>

namespace boost
{

template <class T, class CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, std::optional<T>*, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    T n = boost::lexical_cast<T>(s);
    v = boost::any(std::make_optional<T>(n));
}

} // namespace boost
