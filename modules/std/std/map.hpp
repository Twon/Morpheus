/// \file map.hpp
///     Modularisation for https://eel.is/c++draft/associative.map.syn
export namespace std
{

// [map], class template map
using std::map;

using std::operator==;
using std::operator<=>;

using std::swap;

// [map.erasure], erasure for map
using std::erase_if;

// [multimap], class template multimap
using std::multimap;

using std::operator==;
using std::operator<=>;

using std::swap;

// [multimap.erasure], erasure for map
using std::erase_if;

namespace pmr
{
using std::pmr::map;
using std::pmr::multimap;
} // namespace pmr

} // namespace std
