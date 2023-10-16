#pragma once

#include <concepts>
#include <functional>
#include <morpheus/core/conformance/version.hpp>
#include <morpheus/core/meta/invocable_traits.hpp>
#include <type_traits>
#include <utility>

#if (__cpp_lib_function_ref >= 202202L)

namespace morpheus
{
namespace func_ref_ns = std;
}

#else

namespace morpheus::func_ref_ns
{

/// \struct nontype_t
///     nontype argument tag
/// \note
///     Proposed by p2472r3: make function_ref more functional
template <auto V>
struct nontype_t
{
    explicit nontype_t() = default;
};

template <auto V>
inline constexpr nontype_t<V> nontype{};

template <class Signature>
class function_ref;

/// \class function_ref
///     Implementation of [p0792r10](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p0792r10.html)
///     function_ref, a simple non-owning reference to a callable.  This allows binding to callables of:
///     - Lmabdas/Functors
///     - Free functions
///     - Member functions
/// \note
///      [func.wrap.ref.class]
template <typename Return, class... Args>
class function_ref<Return(Args...)>
{

    static constexpr bool isNoexcept = meta::IsNothrowInvocable<Return, Args...>;
    static constexpr bool isConst = meta::IsConstInvocable<Return, Args...>;

    template <typename... T>
    static constexpr bool isInvokableWith = []()
    {
        if constexpr (isNoexcept)
            return std::is_nothrow_invocable_r_v<Return, T..., Args...>;
        else
            return std::is_invocable_r_v<Return, T..., Args...>;
    }();

    template <typename T>
    using constness = std::conditional_t<isConst, std::add_const_t<T>, T>;

    template <class F>
    requires isInvokableWith<F>
    static constexpr Return invoke(F&& f, Args&&... args) noexcept(isNoexcept)
    {
        if constexpr (std::is_void_v<Return>)
            std::invoke<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
    #if (__cpp_lib_invoke_r >= 202106L)
        else
            return std::invoke_r<Return, F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
    #else
        else
            return std::invoke<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
    #endif
    }

    template <class F, class T>
    requires isInvokableWith<F, constness<T>&>
    static constexpr Return invoke(F&& f, T&& t, Args&&... args) noexcept(isNoexcept)
    {
        if constexpr (std::is_void_v<Return>)
            std::invoke<F, T, Args...>(std::forward<F>(f), std::forward<T>(t), std::forward<Args>(args)...);
    #if (__cpp_lib_invoke_r >= 202106L)
        else
            return std::invoke_r<Return, F, T, Args...>(std::forward<F>(f), std::forward<T>(t), std::forward<Args>(args)...);
    #else
        else
            return std::invoke<F, T, Args...>(std::forward<F>(f), std::forward<T>(t), std::forward<Args>(args)...);
    #endif
    }

public:
    constexpr function_ref() = delete;

    template <class F>
    function_ref(F* f) noexcept
    requires std::is_function_v<F> and isInvokableWith<F>
    : mInvoke([](Storage storage, Args... args) noexcept(isNoexcept) { return invoke(function_ref::get<F>(storage), std::forward<Args>(args)...); })
    , mStorage(f)
    {}

    template <auto F>
    constexpr function_ref(nontype_t<F>) noexcept
    : mInvoke([](Storage, Args... args) noexcept(isNoexcept) { return invoke(F, std::forward<Args>(args)...); })
    {}

    template <auto F, class T>
    constexpr function_ref(nontype_t<F>, T& object) noexcept
        requires isInvokableWith<decltype(F), T&>
    : mInvoke(
          [](Storage storage, Args... args) noexcept(isNoexcept) -> Return
          {
              auto& objectStorage = *function_ref::get<constness<T>>(storage);
              return invoke(F, objectStorage, std::forward<Args>(args)...);
          })
    , mStorage(std::addressof(object))
    {}

    template <auto F, class T>
    constexpr function_ref(nontype_t<F>, constness<T> const* object) noexcept
        requires isInvokableWith<decltype(F), constness<T> const*>
    : mInvoke(
          [](Storage storage, Args... args) noexcept(isNoexcept) -> Return
          {
              constness<T>& objectStorage = *function_ref::get<T>(storage);
              return invoke(F, objectStorage, std::forward<Args>(args)...);
          })
    , mStorage(std::addressof(object))
    {}

    template <class F, class T = std::remove_reference_t<F>>
    constexpr function_ref(F&& f) noexcept
        requires(not std::is_same_v<F, function_ref> and not std::is_member_pointer_v<F> and isInvokableWith<F, constness<T>>)
    : mInvoke(
          [](Storage storage, Args... args) noexcept(isNoexcept) -> Return
          {
              constness<T>& objectStorage = *function_ref::get<T>(storage);
              return invoke(objectStorage, std::forward<Args>(args)...);
          })
    , mStorage(std::addressof(f))
    {}

    template <typename F, class T = std::remove_reference_t<F>>
    function_ref& operator=(F&&)
    requires(not std::is_same_v<F, function_ref> and not std::is_pointer_v<F>)
    = delete;

    constexpr Return operator()(Args... args) const noexcept(isNoexcept) { return mInvoke(mStorage, std::forward<Args>(args)...); }

    constexpr void swap(function_ref& other) noexcept
    {
        std::swap(mInvoke, other.mInvoke);
        std::swap(mStorage, other.mStorage);
    }

private:
    union Storage
    {
        void* p = nullptr;
        void const* cp;
        void (*fp)();

        constexpr Storage() noexcept = default;

        template <class T>
        requires std::is_object_v<T>
        constexpr explicit Storage(T* t) noexcept : p(t)
        {}

        template <class T>
        requires std::is_object_v<T>
        constexpr explicit Storage(T const* t) noexcept : cp(t)
        {}

        template <class F>
        requires std::is_function_v<F>
        constexpr explicit Storage(F* f) noexcept : fp(f)
        {}
    };

    template <typename T>
    requires std::is_object_v<T> or std::is_function_v<T>
    static constexpr auto get(Storage const storage)
    {
        if constexpr (std::is_const_v<T>)
            return static_cast<T const*>(storage.cp);
        else if constexpr (std::is_object_v<T>)
            return static_cast<T*>(storage.p);
        else
            return static_cast<T*>(storage.fp);
    }

    using InternalInvocableType = Return(Storage, Args...);

    InternalInvocableType* mInvoke = nullptr;
    Storage mStorage;
};

// [func.wrap.ref.deduct]
template <class F>
requires std::is_function_v<F>
function_ref(F*) -> function_ref<F>;

template <auto f>
requires std::is_function_v<decltype(f)>
function_ref(nontype_t<f>) -> function_ref<std::remove_pointer_t<decltype(f)>>;

// template<auto f>
// function_ref(nontype_t<f>, auto)->function_ref<see below>;

/*

    template <typename R, typename... Args>
    function_ref(R (*)(Args...)) -> function_ref<R(Args...)>;

    template <typename R, typename... Args>
    function_ref(R (*)(Args...) noexcept) -> function_ref<R(Args...) noexcept>;

    template <typename F>
    function_ref(F) -> function_ref<see below>;
*/

} // namespace morpheus::func_ref_ns
#endif
