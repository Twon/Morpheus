/// \file stacktrace.hpp
///     Modularisation for https://eel.is/c++draft/stacktrace.syn
export namespace std
{

// [stacktrace.entry], class stacktrace_­entry
using std::stacktrace_entry;

// [stacktrace.basic], class template basic_­stacktrace
using std::basic_stacktrace;

// basic_­stacktrace typedef-names
using std::stacktrace;

// [stacktrace.basic.nonmem], non-member functions
using std::swap;

using std::to_string;

using std::operator<<;

namespace pmr {
    using std::pmr::stacktrace;
}

// [stacktrace.basic.hash], hash support
using std::hash;

} // namespace std
