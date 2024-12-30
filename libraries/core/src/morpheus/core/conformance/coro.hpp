#pragma once

// clang-format off
#if __has_include(<coroutine>)
    #include <coroutine> // IWYU pragma: export
    namespace morpheus { namespace coro_ns = std; }
#else
    #include <experimental/coroutine> // IWYU pragma: export
    namespace morpheus { namespace coro_ns = std::experimental; }
#endif
// clang-format on

namespace morpheus::coro
{

// [coroutine.traits], coroutine traits
using coro_ns::coroutine_traits;

// [coroutine.handle], coroutine handle
using coro_ns::coroutine_handle;

// [coroutine.noop], no-op coroutines
using coro_ns::noop_coroutine;
using coro_ns::noop_coroutine_handle;
using coro_ns::noop_coroutine_promise;

// [coroutine.trivial.awaitables], trivial awaitables
using coro_ns::suspend_always;
using coro_ns::suspend_never;

} // namespace morpheus::coro
