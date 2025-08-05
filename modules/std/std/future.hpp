/// \file future.hpp
///     Modularisation for https://eel.is/c++draft/future.syn
export namespace std
{

using std::future_errc;

using std::launch;

using std::future_status;

// [futures.errors], error handling
using std::is_error_code_enum;
using std::make_error_code;
using std::make_error_condition;

using std::future_category;

// [futures.future.error], class future_error
using std::future_error;

// [futures.promise], class template promise
using std::promise;

using std::swap;

using std::uses_allocator;

// [futures.unique.future], class template future
using std::future;

// [futures.shared.future], class template shared_future
using std::shared_future;

// [futures.task], class template packaged_task
using std::packaged_task;

using std::swap;

// [futures.async], function template async
using std::async;

} // namespace std
