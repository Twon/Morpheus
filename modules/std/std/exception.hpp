/// \file exception.hpp
///     Modularisation for https://eel.is/c++draft/exception.syn
export namespace std
{

using std::exception;
using std::bad_exception;
using std::nested_exception;

using std::terminate_handler;
using std::get_terminate;
using std::set_terminate;
using std::terminate;

using std::uncaught_exceptions;

using std::exception_ptr;

using std::current_exception;
using std::rethrow_exception;
using std::make_exception_ptr;

using std::throw_with_nested;
using std::rethrow_if_nested;

} // namespace std
