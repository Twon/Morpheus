#pragma once

#include <morpheus/core/conformance/version.hpp>
#include <morpheus/core/meta/invocable_traits.hpp>
#include <concepts>
#include <type_traits>
#include <utility>

#if (__cpp_lib_function_ref >= 202202L)

namespace morpheus { namespace func_ref_ns = std; }

#else

namespace morpheus::func_ref_ns 
{

/// \struct nontype_t
///     nontype argument tag
/// \note
///     Proposed by p2472r3: make function_ref more functional
template<auto V>
struct nontype_t {
    explicit nontype_t() = default;
};

template<auto V> inline constexpr nontype_t<V> nontype{};

template<class Signature> class function_ref; 

/// \class function_ref
///     Implementation of [p0792r10](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p0792r10.html) 
///     function_ref, a simple non-owning reference to a callable.  This allows binding to callables of:
///     - Lmabdas/Functors
///     - Free functions
///     - Member functions
/// \note
///      [func.wrap.ref.class]
template<typename Return, class... Args>
class function_ref<Return(Args...)> {
public:
    using signature_type = Return(*)(Args...);

    constexpr function_ref() = delete;

    template<class F>
    function_ref(F* f) noexcept requires std::is_function_v<F> and isInvokableWith<F>
    :   mInvoke( 
            [](Storage storage, Args&&... args) noexcept(isNoexcept)
            {
                if constexpr (std::is_void_v<Return>)
                    function_ref::get<F>(storage)(std::forward<Args>(args)...);
                else
                    return function_ref::get<F>(storage)(std::forward<Args>(args)...);
            })
    ,   mStorage(f)
    {}

    template<auto f> constexpr function_ref(nontype_t<f>) noexcept
    {

    }

//    template<auto f, class T> constexpr function_ref(nontype_t<f>, T&) noexcept;
//    template<auto f, class T> constexpr function_ref(nontype_t<f>, cv T*) noexcept;

    function_ref(function_ref const&) noexcept = default;

   /*  

    template <typename F>
    function_ref(F&&);

    function_ref& operator=(const function_ref&) noexcept = default;

    template <typename F>
    function_ref& operator=(F&&);

    void swap(function_ref&) noexcept;

    R operator()(Args...) const noexcept(see below);*/

    constexpr Return operator()(Args&&... args) const noexcept(isNoexcept)
    {
        return mInvoke(mStorage, std::forward<Args>(args)...);
    }

    constexpr void swap(function_ref& other) noexcept
    {
        std::swap(mInvoke, other.mInvoke);
        std::swap(mStorage, other.mStorage);
    }

private:
    static constexpr bool isNoexcept = meta::IsNothrowInvocable<Return, Args...>;
    static constexpr bool isConst = meta::IsConstInvocable<Return, Args...>;

    template<typename F>
    static constexpr bool isInvokableWith = []()
    {
        if constexpr (isNoexcept)
            return std::is_nothrow_invocable_r_v<Return, F, Args...>;
        else
            return std::is_invocable_r_v<Return, F, Args...>;
    }();

    union Storage
    {
        void* p = nullptr;
        void const* cp;
        void (*fp)();

        constexpr Storage() noexcept = default;

        template<class T> requires std::is_object_v<T>
        constexpr explicit Storage(T* t) noexcept : p(t)
        {}

        template<class T> requires std::is_object_v<T>
        constexpr explicit Storage(T const* t) noexcept : cp(t)
        {}

        template<class F> requires std::is_function_v<F>
        constexpr explicit Storage(F* f) noexcept : fp(f)
        {}
    };

    template<typename T> requires std::is_object_v<T> or std::is_function_v<T>
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
template<class F> requires std::is_function_v<F>
function_ref(F*)->function_ref<F>;

template<auto f> requires std::is_function_v<decltype(f)>
function_ref(nontype_t<f>)->function_ref<std::remove_pointer_t<decltype(f)>>;

//template<auto f>
//function_ref(nontype_t<f>, auto)->function_ref<see below>;


/*
    template <typename Signature>
    void swap(function_ref<Signature>&, function_ref<Signature>&) noexcept;

    template <typename R, typename... Args>
    function_ref(R (*)(Args...)) -> function_ref<R(Args...)>;

    template <typename R, typename... Args>
    function_ref(R (*)(Args...) noexcept) -> function_ref<R(Args...) noexcept>;

    template <typename F>
    function_ref(F) -> function_ref<see below>;
*/

}
#endif
