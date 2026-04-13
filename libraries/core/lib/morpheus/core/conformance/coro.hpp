#pragma once

// clang-format off
#if __has_include(<coroutine>)
    #include <coroutine> // IWYU pragma: export
    namespace morpheus::conf { namespace coro = ::std; }
#else
    #include <experimental/coroutine> // IWYU pragma: export
    namespace morpheus::conf { namespace coro = ::std::experimental; }
#endif
// clang-format on

namespace morpheus::concurrency::coro
{

// [coroutine.traits], coroutine traits
using conf::coro::coroutine_traits;

// [coroutine.handle], coroutine handle
using conf::coro::coroutine_handle;

// [coroutine.noop], no-op coroutines
using conf::coro::noop_coroutine;
using conf::coro::noop_coroutine_handle;
using conf::coro::noop_coroutine_promise;

// [coroutine.trivial.awaitables], trivial awaitables
using conf::coro::suspend_always;
using conf::coro::suspend_never;

} // namespace morpheus::concurrency::coro
