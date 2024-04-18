/// \file string_view.hpp
///     Modularisation for https://eel.is/c++draft/string_view.syn
export namespace std
{

// [string.view.template], class template basic_string_view
using std::basic_string_view;

// basic_string_view typedefs
using std::string_view;
using std::u16string_view;
using std::u32string_view;
using std::u8string_view;
using std::wstring_view;

// [string.view.hash], hash support
using std::hash;

} // namespace std
