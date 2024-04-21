/// \file flat_set.hpp
///     Modularisation for https://eel.is/c++draft/flat.set.syn
export namespace std
{

// [flat.set], class template flat_set
using std::flat_map;

using std::sorted_unique;
using std::sorted_unique_t;

using std::uses_allocator;

// [flat.set.erasure], erasure for flat_set
using std::erase_if;

// [flat.multiset], class template flat_multiset
using std::flat_multimap;

using std::sorted_equivalent;
using std::sorted_equivalent_t;

using std::uses_allocator;

// [flat.multiset.erasure], erasure for flat_multiset
using std::erase_if;

} // namespace std
