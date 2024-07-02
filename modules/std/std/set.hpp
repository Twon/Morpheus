/// \file set.hpp
///     Modularisation for https://eel.is/c++draft/associative.set.syn
export namespace std
{

// [set], class template map
using std::set;

using std::operator==;
using std::operator<=>;

using std::swap;

// [set.erasure], erasure for set
using std::erase_if;

// [multiset], class template multiset
using std::multiset;

using std::operator==;
using std::operator<=>;

using std::swap;

// [multiset.erasure], erasure for set
using std::erase_if;

namespace pmr
{
using std::pmr::set;
using std::pmr::multiset;
} // namespace pmr

} // namespace std
