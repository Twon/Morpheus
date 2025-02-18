/// \file vector.hpp
///     Modularisation for https://eel.is/c++draft/vector.syn
export namespace std
{

// [vector], class template vector
using std::vector;

using std::operator==;
using std::operator<=>;

using std::swap;

// [vector.erasure], erasure
using std::erase;
using std::erase_if;

namespace pmr {
    using std::pmr::vector;
}

// hash support
using std::hash;

#if (__cpp_lib_format_ranges >= 202207L)

    // [vector.bool.fmt], formatter specialization for vector<bool>
    using std::formatter;

#endif // #if (__cpp_lib_format_ranges >= 202207L)

} // namespace std
