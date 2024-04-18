/// \file list.hpp
///     Modularisation for https://eel.is/c++draft/list.syn
export namespace std
{

// [list], class template list
using std::list;

using std::operator==;
using std::operator<=>;

using std::swap;

// [list.erasure], erasure
using std::erase;
using std::erase_if;

namespace pmr
{
using std::pmr::list;
} // namespace pmr

} // namespace std
