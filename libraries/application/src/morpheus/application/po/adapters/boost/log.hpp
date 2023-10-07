#pragma once

#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <vector>


namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace trivial {

template <class CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, severity_level* p, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);

    using namespace boost::log::trivial;
    if (boost::iequals(s, "trace"))
        v = trace;
    else if (boost::iequals(s, "debug"))
        v = debug;
    else if (boost::iequals(s, "info"))
        v = info;
    else if (boost::iequals(s, "warning"))
        v = warning;
    else if (boost::iequals(s, "error"))
        v = error;
    else if (boost::iequals(s, "fatal"))
        v = fatal;
    else
        throw po::validation_error(po::validation_error::invalid_option_value);
}

}

BOOST_LOG_CLOSE_NAMESPACE

} // namespace boost::log::trivial