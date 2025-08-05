/// \file charconv.hpp
///     Modularisation for https://eel.is/c++draft/charconv.syn
export namespace std
{

// floating-point format for primitive numerical conversion
using std::chars_format;

// [charconv.to.chars], primitive numerical output conversion
using std::to_chars_result;
using std::to_chars;

// [charconv.from.chars], primitive numerical input conversion
using std::from_chars_result;
using std::from_chars;

} // namespace std
