/// \file locale.hpp
///     Modularisation for https://eel.is/c++draft/locale.syn
export namespace std
{

// [locale], locale
using std::locale;
using std::use_facet;
using std::has_facet;

// [locale.convenience], convenience interfaces
using std::isspace;
using std::isprint;
using std::iscntrl;
using std::isupper;
using std::islower;
using std::isalpha;
using std::isdigit;
using std::ispunct;
using std::isxdigit;
using std::isalnum;
using std::isgraph;
using std::isblank;
using std::toupper;
using std::tolower;

// [category.ctype], ctype
using std::ctype;
using std::ctype_byname;
using std::codecvt_base;
using std::codecvt;
using std::codecvt_byname;

// [category.numeric], numeric
using std::num_get;
using std::num_put;
using std::numpunct;
using std::numpunct_byname;

// [category.collate], collation
using std::collate;
using std::collate_byname;

// [category.time], date and time
using std::time_base;
using std::time_get;
using std::time_get_byname;
using std::time_put;
using std::time_put_byname;

// [category.monetary], money
using std::money_base;
using std::money_get;
using std::money_put;
using std::moneypunct;
using std::moneypunct_byname;

// [category.messages], message retrieval
using std::messages_base;
using std::messages;
using std::messages_byname;

} // namespace std
