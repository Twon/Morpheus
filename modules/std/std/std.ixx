
module;

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <cctype>
#include <charconv>
#include <cstdint>
#include <compare>
#include <concepts>
#include <condition_variable>
#include <deque>
#if __has_include(<debugging>)
    #include <debugging>
#endif
#include <exception>
#include <execution>
#if __has_include(<expected>)
    #include <expected>
#endif
#include <filesystem>
#if __has_include(<flat_map>)
    #include <flat_map>
#endif
#if __has_include(<flat_set>)
    #include <flat_set>
#endif
#if __has_include(<format>)
    #include <format>
#endif
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#if __has_include(<generator>)
    #include <generator>
#endif
#if __has_include(<hazard_pointer>)
    #include <hazard_pointer>
#endif
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <latch>
#include <list>
#include <locale>
#include <map>
#include <mutex>
#if __has_include(<rcu>)
    #include <rcu>
#endif
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <stacktrace>
#include <stop_token>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

export module std;

#include "algorithm.hpp"
#include "any.hpp"
#include "array.hpp"
#include "atomic.hpp"
#include "barrier.hpp"
#include "bit.hpp"
#include "bitset.hpp"
#include "cctype.hpp"
#include "charconv.hpp"
#include "cstdint.hpp"
#include "concepts.hpp"
#include "compare.hpp"
#include "condition_variable.hpp"
#include "deque.hpp"
#if __has_include(<debugging>)
    #include "debugging.hpp"
#endif
#include "exception.hpp"
#include "execution.hpp"
#if __has_include(<expected>)
    #include "expected.hpp"
#endif
#include "filesystem.hpp"
#if __has_include(<flat_map>)
    #include "flat_map.hpp"
#endif
#if __has_include(<flat_set>)
    #include "flat_set.hpp"
#endif
#if __has_include(<format>)
    #include "format.hpp"
#endif
#include "forward_list.hpp"
#include "fstream.hpp"
#include "functional.hpp"
#include "future.hpp"
#if __has_include(<generator>)
    #include "generator.hpp"
#endif
#if __has_include(<hazard_pointer>)
    #include "hazard_pointer.hpp"
#endif
#include "initializer_list.hpp"
#include "iomanip.hpp"
#include "ios.hpp"
#include "latch.hpp"
#include "list.hpp"
#include "locale.hpp"
#include "map.hpp"
#include "mutex.hpp"
#if __has_include(<rcu>)
    #include "rcu.hpp"
#endif
#include "semaphore.hpp"
#include "set.hpp"
#include "shared_mutex.hpp"
#include "string.hpp"
#include "source_location.hpp"
#include "stacktrace.hpp"
#include "stop_token.hpp"
#include "string_view.hpp"
#include "type_traits.hpp"
#include "vector.hpp"

#pragma warning(push)
#pragma warning(disable : 5244) // '#include <meow>' in the purview of module 'std' appears erroneous.


#pragma warning(pop)
