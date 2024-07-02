/// \file condition_variable.hpp
///     Modularisation for https://eel.is/c++draft/condition.variable.syn
export namespace std
{

// [thread.condition.condvar], class condition_variable
using std::condition_variable;

// [thread.condition.condvarany], class condition_variable_any
using std::condition_variable_any;

// [thread.condition.nonmember], non-member functions
using std::notify_all_at_thread_exit;

using std::cv_status;

} // namespace std
