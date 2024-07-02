/// \file shared_mutex.hpp
///     Modularisation for https://eel.is/c++draft/shared.mutex.syn
export namespace std
{

// [thread.sharedmutex.class], class shared_mutex
using std::shared_mutex;

// [thread.sharedtimedmutex.class], class shared_timed_mutex
using std::shared_timed_mutex;

// [thread.lock.shared], class template shared_lock
using std::shared_lock;
using std::swap;

} // namespace std
