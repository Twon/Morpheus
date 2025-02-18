/// \file mutex.hpp
///     Modularisation for https://eel.is/c++draft/mutex.syn
export namespace std
{

// [thread.mutex.class], class mutex
using std::mutex;

// [thread.mutex.recursive], class recursive_mutex
using std::recursive_mutex;

// [thread.timedmutex.class] class timed_mutex
using std::timed_mutex;

// [thread.timedmutex.recursive], class recursive_timed_mutex
using std::recursive_timed_mutex;

using std::defer_lock_t;
using std::try_to_lock_t;
using std::adopt_lock_t;

using std::defer_lock;
using std::try_to_lock;
using std::adopt_lock;

// [thread.lock], locks
using std::lock_guard;
using std::scoped_lock;
using std::unique_lock;

using std::swap;

// [thread.lock.algorithm], generic locking algorithms
using std::try_lock;
using std::lock;

using std::once_flag;

using std::call_once;

} // namespace std
