/// \file array.hpp
///     Modularisation for https://eel.is/c++draft/array.syn
export namespace std
{

// [array], class template array
using std::array;

using std::operator==;
using std::operator<=>;

// [array.special], specialized algorithms
using std::swap;

// [array.creation], array creation functions
using std::to_array;

// [array.tuple], tuple interface
using std::tuple_size;
using std::tuple_element;
using std::get;

} // namespace std
