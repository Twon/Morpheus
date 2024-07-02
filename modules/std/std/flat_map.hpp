/// \file flat_map.hpp
///     Modularisation for https://eel.is/c++draft/flat.map.syn
export namespace std
{

// [flat.map], class template flat_map
using std::flat_map;

using std::sorted_unique_t;
using std::sorted_unique;

using std::uses_allocator;

// [flat.map.erasure], erasure for flat_map
using std::erase_if;

// [flat.multimap], class template flat_multimap
using std::flat_multimap;

using std::sorted_equivalent_t;
using std::sorted_equivalent;

using std::uses_allocator;

// [flat.multimap.erasure], erasure for flat_multimap
using std::erase_if;

} // namespace std
