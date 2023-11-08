#pragma once

#include <morpheus/core/base/prerequisites.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/program_options.hpp>

#include <string>
#include <vector>

namespace boost::urls
{

template <class CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& values, url* p, int)
{
    namespace po = boost::program_options;
    po::validators::check_first_occurrence(v);
    auto const& s = po::validators::get_single_string(values);
    /*
    auto const address = boost::asio::ip::make_address(s, ec);
    if (ec == boost::asio::error::invalid_argument) {
        throw po::validation_error(po::validation_error::invalid_option_value);
    }

    v = address;
    */
}

} // namespace boost::urls
