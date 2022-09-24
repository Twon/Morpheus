#pragma once

#if __has_include(<coroutine>)
#   include <coroutine>
namespace morpheus { namespace coro_ns = std; }
#else
#   include <experimental/coroutine>
namespace morpheus { namespace coro_ns = std::experimental; }
#endif

namespace morpheus::coro {

  // [coroutine.traits], coroutine traits
  using coro_ns::coroutine_traits;

  // [coroutine.handle], coroutine handle
  using coro_ns::coroutine_handle;

  // [coroutine.noop], no-op coroutines
  using coro_ns::noop_coroutine_promise;
  using coro_ns::noop_coroutine_handle;
  using coro_ns::noop_coroutine;

  // [coroutine.trivial.awaitables], trivial awaitables
  using coro_ns::suspend_never;
  using coro_ns::suspend_always;

}
