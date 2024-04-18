/// \file string.hpp
///     Modularisation for https://eel.is/c++draft/string.syn
export namespace std
{

// [char.traits], character traits
using std::char_traits;

// [basic.string], basic_string
using std::basic_string;

// basic_string typedefs
using std::string;
using std::u16string;
using std::u32string;
using std::u8string;
using std::wstring;

// [basic.string.hash], hash support
using std::hash;

} // namespace std
