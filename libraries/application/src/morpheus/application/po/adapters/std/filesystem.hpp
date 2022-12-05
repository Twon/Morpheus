#pragma once

#include <boost/any.hpp>

#include <filesystem>
#include <string>
#include <vector>


namespace morpheus::application::po
{

template <class CharType>
void validate(boost::any& v, std::vector<std::basic_string<CharType>> const& s, std::filesystem::path* p, int)
{

}

} // namespace morpheus::application::po