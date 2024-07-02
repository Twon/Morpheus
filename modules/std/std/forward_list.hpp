/// \file forward_list.hpp
///     Modularisation for https://eel.is/c++draft/forward.list.syn
export namespace std
{

// [forward.list], class template forward_list
using std::forward_list;

using std::operator==;
using std::operator<=>;

using std::swap;

// [forward.list.erasure], erasure
using std::erase;
using std::erase_if;

namespace pmr
{

using std::pmr::forward_list;

} // namespace pmr


} // namespace std
