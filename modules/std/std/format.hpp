/// \file format.hpp
///     Modularisation for https://eel.is/c++draft/format.syn
export namespace std
{

// [format.context], class template basic_format_context
using std::basic_format_context;
using std::format_context;
using std::wformat_context;

// [format.args], class template basic_format_args
using std::basic_format_args;
using std::format_args;
using std::wformat_args;

// [format.fmt.string], class template basic_format_string
using std::basic_format_string;
using std::format_string;
using std::wformat_string;
#if (__cpp_lib_format >= 202311L)
    using std::runtime_format;
#endif // #if (__cpp_lib_format >= 202311L)

// [format.functions], formatting functions
using std::format;
using std::vformat;
using std::format_to;
using std::vformat_to;

using std::format_to_n_result;
using std::format_to_n_result;
using std::formatted_size;

// [format.formatter], formatter
using std::formatter;

#if (__cpp_lib_format_ranges >= 202207L)
    // [format.formattable], concept formattable
    using std::formattable;
#endif // #if (__cpp_lib_format_ranges >= 202207L)

// [format.parse.ctx], class template basic_format_parse_context
using std::basic_format_parse_context;
using std::format_parse_context;
using std::wformat_parse_context;

#if (__cpp_lib_format_ranges >= 202207L)
    // [format.range], formatting of ranges
    // [format.range.fmtkind], variable template format_kind
    using std::format_kind;
    using std::range_format;

    // [format.range.formatter], class template range_formatter
    using std::range_formatter;
#endif // #if (__cpp_lib_format_ranges >= 202207L)

// [format.arguments], arguments
// [format.arg], class template basic_format_arg
using std::basic_format_arg;
using std::visit_format_arg; // Deprecated in C++26

using std::make_format_args;
using std::make_wformat_args;

// [format.error], class format_error
using std::format_error;

} // namespace std
