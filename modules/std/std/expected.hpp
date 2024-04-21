/// \file expected.hpp
///     Modularisation for https://eel.is/c++draft/expected.syn
export namespace std
{

// [expected.unexpected], class template unexpected
using std::unexpected;

// [expected.bad], class template bad_expected_access
// [expected.bad.void], specialization for void
using std::bad_expected_access;

// in-place construction of unexpected values
using std::unexpect_t;
using std::unexpect;

// [expected.expected], class template expected
// [expected.void], partial specialization of expected for void types
using std::expected;

} // namespace std
