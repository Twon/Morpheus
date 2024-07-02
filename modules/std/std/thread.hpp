/// \file thread.hpp
///     Modularisation for https://eel.is/c++draft/thread.syn
export namespace std
{

// [thread.thread.class], class thread
using std::thread;

using std::swap;

// [thread.jthread.class], class jthread
#if (__cpp_lib_jthread>=201911L)
   using std::jthread;
#endif // #if (__cpp_lib_jthread>=201911L)

// [thread.thread.this], namespace this_thread
namespace this_thread {

   using std::this_thread::get_id;

   using std::this_thread::yield;
   using std::this_thread::sleep_until;
   using std::this_thread::sleep_for;

}

// [thread.thread.id]
using std::operator==;
using std::operator<=>;

using std::operator<<;

#if (__cpp_lib_formatters < 202302L)
    using std::formatter;
#endif // #if (__cpp_lib_formatters < 202302L)

using std::hash;

} // namespace std
