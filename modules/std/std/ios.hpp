/// \file ios.hpp
///     Modularisation for https://eel.is/c++draft/ios.syn
export namespace std
{

using std::streamoff;
using std::streamsize;
using std::fpos;

using std::ios_base;
using std::basic_ios;

// [std.ios.manip], manipulators
using std::boolalpha;
using std::noboolalpha;

using std::showbase;
using std::noshowbase;

using std::showpoint;
using std::noshowpoint;

using std::showpos;
using std::noshowpos;

using std::skipws;
using std::noskipws;

using std::uppercase;
using std::nouppercase;

using std::unitbuf;
using std::nounitbuf;

// [adjustfield.manip], adjustfield
using std::internal;
using std::left;
using std::right;

// [basefield.manip], basefield
using std::dec;
using std::hex;
using std::oct;

// [floatfield.manip], floatfield
using std::fixed;
using std::scientific;
using std::hexfloat;
using std::defaultfloat;

// [error.reporting], error reporting
using std::io_errc;

using std::is_error_code_enum;
using std::make_error_code;
using std::make_error_condition;
using std::iostream_category;

} // namespace std
