#pragma once

#include <boost/any.hpp>
#include <boost/program_options.hpp>

#include <optional>
#include <string>
#include <vector>

#if BOOST_VERSION < 109000  // before 1.90 added std::optional support
namespace boost::program_options 
{

template <class T, class CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, std::optional<T>*, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    boost::any n;
    validate(n, values, static_cast<T*>(nullptr), 0);
    v = boost::any(std::optional<T>(boost::any_cast<T>(n)));
}

} // namespace boost::program_options
#endif // BOOST_VERSION < 109000  // before 1.90 added std::optional support 
