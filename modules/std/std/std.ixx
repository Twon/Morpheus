
module;

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <cctype>
#include <cstdint>
#include <compare>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <functional>
#if __has_include(<rcu>)
    #include <hazard_pointer>
#endif
#include <future>
#include <latch>
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
#include "cstdint.hpp"
#include "concepts.hpp"
#include "compare.hpp"
#include "condition_variable.hpp"
#include "deque.hpp"
#if __has_include(<rcu>)
    #include "hazard_pointer.hpp"
#endif
#include "functional.hpp"
#include "future.hpp"
#include "latch.hpp"
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
