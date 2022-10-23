#pragma once

#include <core/conformance/version.hpp>
#include <concepts>

#if (__cpp_lib_function_ref >= 202202L)

namespace morpheus { namespace func_ref_ns = std; }

#else

namespace morpheus::func_ref_ns 
{
template<class Signature> class function_ref; 

/// \class function_ref
///     Implementation of [p0792r10](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p0792r10.html) 
///     function_ref, a simple non-owning reference to a callable.
template<typename Return, class... ArgTypes>
class function_ref<Return(ArgTypes...)> {
public:
    using signature_type = Return(*)(ArgTypes...);

    constexpr function_ref() = delete;

/*  
    function_ref(const function_ref&) noexcept = default;

    template <typename F>
    function_ref(F&&);

    function_ref& operator=(const function_ref&) noexcept = default;

    template <typename F>
    function_ref& operator=(F&&);

    void swap(function_ref&) noexcept;

    R operator()(Args...) const noexcept(see below);*/
private:


};

// [func.wrap.ref.deduct]
template<class F>
function_ref(F*)->function_ref<F>;

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
