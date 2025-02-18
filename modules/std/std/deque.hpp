/// \file deque.hpp
///     Modularisation for https://eel.is/c++draft/deque.syn
export namespace std
{

// [deque], class template deque
using std::deque;

using std::operator==;
using std::operator<=>;

using std::swap;

// [deque.erasure], erasure
using std::erase;
using std::erase_if;

namespace pmr
{
    using std::pmr::deque;
}

} // namespace std
