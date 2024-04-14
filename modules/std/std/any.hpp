/// \any.hpp Modularisation for https://eel.is/c++draft/any.synop
export namespace std
{

// [any.bad.any.cast], class bad_any_cast
using std::bad_any_cast;

// [any.class], class any
using std::any;

// [any.nonmembers], non-member functions
using std::any_cast;
using std::make_any;
using std::swap;

} // namespace std
