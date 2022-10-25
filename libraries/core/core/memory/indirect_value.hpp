#pragma once

#include "core/base/compiler.hpp"
#include "core/conformance/version.hpp"
#include "core/meta/concepts/complete.hpp"

#include <concepts>
#include <exception>
#include <memory>
#include <type_traits>

namespace morpheus::memory
{

template <class T>
struct default_copy {
  using deleter_type = std::default_delete<T>;
  constexpr T* operator()(const T& t) const { return new T(t); }
};

template <class T, class = void>
struct copier_traits_deleter_base {};

template <class T>
struct copier_traits_deleter_base<T, std::void_t<typename T::deleter_type>> {
  using deleter_type = typename T::deleter_type;
};

template <class U, class V>
struct copier_traits_deleter_base<U* (*)(V)> {
  using deleter_type = void (*)(U*);
};

// The user may specialize copier_traits<T> per [namespace.std]/2.
template <class T>
struct copier_traits : copier_traits_deleter_base<T, void> {};

/// \class bad_indirect_value_access
///     Exception type thrown upon a accessing an indirect_value with no underlying value assigned.
class bad_indirect_value_access : public std::exception {
public:
    const char* what() const noexcept override {
        return "bad_indirect_value_access";
    }
};

namespace detail
{

template <typename T, typename A, typename... Args>
constexpr T* allocate_object(A& a, Args&&... args)
{
    using t_allocator = typename std::allocator_traits<A>::template rebind_alloc<T>;
    using t_traits = std::allocator_traits<t_allocator>;
    t_allocator t_alloc(a);
    T* mem = t_traits::allocate(t_alloc, 1);
    try {
        t_traits::construct(t_alloc, mem, std::forward<Args>(args)...);
        return mem;
    } catch (...) {
        t_traits::deallocate(t_alloc, mem, 1);
        throw;
    }
}

template <typename T, typename A>
constexpr void deallocate_object(A& a, T* p)
{
    using t_allocator = typename std::allocator_traits<A>::template rebind_alloc<T>;
    using t_traits = std::allocator_traits<t_allocator>;
    t_allocator t_alloc(a);
    t_traits::destroy(t_alloc, p);
    t_traits::deallocate(t_alloc, p, 1);
};

template <class T, class A>
struct allocator_delete : A
{
    constexpr allocator_delete(A& a) : A(a) {} 
    constexpr void operator()(T* ptr) const noexcept
    { 
        static_assert(0 < sizeof(T), "can't delete an incomplete type");
        detail::deallocate_object(*this, ptr);
    }
};

template <class T, class A>
struct allocator_copy : A 
{
    constexpr allocator_copy(A& a) : A(a) {} 
    using deleter_type = allocator_delete<T, A>;
    constexpr T* operator()(const T& t) const
    { 
        return detail::allocate_object<T>(*this, t);
    }
};

/// \struct exchange_on_move_ptr
///     Thin wrapper for a pointer to ensure moving of pointers resutls in a exchange with nullptr.  Use ensures 
///     containing classes can rely on the rule of zero for special memmber functions. 
template<typename T>
struct exchange_on_move_ptr
{
    constexpr exchange_on_move_ptr() noexcept = default;
    constexpr exchange_on_move_ptr(T* p) noexcept
    :   ptr(p)
    {
    }
    constexpr exchange_on_move_ptr(exchange_on_move_ptr const&) noexcept = default;
    constexpr exchange_on_move_ptr(exchange_on_move_ptr&& rhs) noexcept
    :   ptr(std::exchange(rhs.ptr, nullptr))
    {}

    constexpr exchange_on_move_ptr& operator=(exchange_on_move_ptr const&) noexcept = default;
    constexpr exchange_on_move_ptr& operator=(exchange_on_move_ptr&& rhs) noexcept
    {
        ptr = std::exchange(rhs.ptr, nullptr);
        return *this;
    }

    constexpr exchange_on_move_ptr& operator=(T* p) noexcept { ptr = p; return *this; }
    constexpr explicit(false) operator T*() const noexcept { return ptr; }

    friend T* exchange(exchange_on_move_ptr& lhs, auto rhs) { return std::exchange(lhs.ptr, rhs); }

    T* ptr = nullptr;
};

template<typename T, typename C, typename D>
struct indirect_value_base;

/// \class indirect_value_base
///     We must specialise to handle the case where copier and deleter are the same object and have no size.  In this 
///     case this we have [[no_unique_address]] pointing to two objects of the same type which is not allowed by the 
///     standard.  To support this we specialises away the unnecessary duplication of the object to avoid unnecessary
///     storage and in-doing so resolve the any issues around use of [[no_unique_address]]: 
///     https://en.cppreference.com/w/cpp/language/attributes/no_unique_address
/// \tparam T The underluing value type
/// \tparam CD The combined copier and deleter object
template<typename T, typename CD>
struct indirect_value_base<T, CD, CD>
{
    exchange_on_move_ptr<T> mValue;

#if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    [[msvc::no_unique_address]] CD mCopierDeleterCombined;
#else
    [[no_unique_address]] CD mCopierDeleterCombined;
#endif

#if (__cpp_explicit_this_parameter >= 202110)
    template<typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> getC(this Self&& self) { return mCopierDeleterCombined; }

    template<typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> getD(this Self&& self) { return mCopierDeleterCombined; }
#else
    [[nodiscard]] auto& getC() & { return mCopierDeleterCombined; }
    [[nodiscard]] auto const& getC() const & { return mCopierDeleterCombined; }
    [[nodiscard]] auto&& getC() && { return std::move(mCopierDeleterCombined); }
    [[nodiscard]] auto const&& getC() const && { return  std::move(mCopierDeleterCombined); }
    [[nodiscard]] auto& getD() & { return mCopierDeleterCombined; }
    [[nodiscard]] auto const& getD() const & { return mCopierDeleterCombined; }
    [[nodiscard]] auto&& getD() && { return std::move(mCopierDeleterCombined); }
    [[nodiscard]] auto const&& getD() const && { return  std::move(mCopierDeleterCombined); }
#endif

    constexpr void swap(indirect_value_base& rhs) noexcept(std::is_nothrow_swappable_v<CD>)
    {
        using std::swap;
        swap(mValue, rhs.mValue);
        swap(mCopierDeleterCombined, rhs.mCopierDeleterCombined);
    }
};

template<typename T, typename C, typename D>
struct indirect_value_base
{
    exchange_on_move_ptr<T> mValue;

#if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    [[msvc::no_unique_address]] C mCopier;
    [[msvc::no_unique_address]] D mDeleter;
#else
    [[no_unique_address]] C mCopier;
    [[no_unique_address]] D mDeleter;
#endif

#if (__cpp_explicit_this_parameter >= 202110)
    template<typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> getC(this Self&& self) { return mCopier; }

    template<typename Self>
    [[nodiscard]] std::copy_cvref_t<Self, auto> getD(this Self&& self) { return mDeleter; }
#else
    [[nodiscard]] auto& getC() & { return mCopier; }
    [[nodiscard]] auto const& getC() const & { return mCopier; }
    [[nodiscard]] auto&& getC() && { return std::move(mCopier); }
    [[nodiscard]] auto const&& getC() const && { return  std::move(mCopier); }
    [[nodiscard]] auto& getD() & { return mDeleter; }
    [[nodiscard]] auto const& getD() const & { return mDeleter; }
    [[nodiscard]] auto&& getD() && { return std::move(mDeleter); }
    [[nodiscard]] auto const&& getD() const && { return  std::move(mDeleter); }
#endif

    constexpr void swap(indirect_value_base& rhs) noexcept(std::is_nothrow_swappable_v<C> && std::is_nothrow_swappable_v<D>)
    {
        using std::swap;
        swap(mValue, rhs.mValue);
        swap(mCopier, rhs.mCopier);
        swap(mDeleter, rhs.mDeleter);
    }
};

}

/// \class indirect_value
///     Implements P1950R2, a free-store-allocated value type for C++ 
/// \tparam T The underlying value type.
/// \tparam Copier The copier functor to customise how the underlying value is copied.
/// \tparam Deleter The deleter functor to customise how the underlying value is deleted.
template<
    typename T, 
    std::invocable<T const&> Copier = default_copy<T>,
    std::invocable<T*> Deleter = typename copier_traits<Copier>::deleter_type
>
requires std::same_as<std::invoke_result_t<Copier, T const&>, T*>
class indirect_value : public detail::indirect_value_base<T, Copier, Deleter>
{
    using base_type = detail::indirect_value_base<T, Copier, Deleter>;

public:
    using value_type = T;
    using copier_type = Copier;
    using deleter_type = Deleter;

    constexpr indirect_value() noexcept(std::is_nothrow_default_constructible_v<copier_type> &&
                                        std::is_nothrow_default_constructible_v<deleter_type>) = default;

    template <class... Ts>
    requires(std::is_constructible_v<T, Ts...>)
    constexpr explicit indirect_value(std::in_place_t, Ts&&... ts)
    :   base_type{ new T(std::forward<Ts>(ts)...) }
    {}

    constexpr explicit indirect_value(T* t) noexcept(std::is_nothrow_default_constructible_v<copier_type> &&
                                                     std::is_nothrow_default_constructible_v<deleter_type>) 
        requires(std::is_default_constructible_v<copier_type> && not std::is_pointer_v<copier_type> &&
                 std::is_default_constructible_v<deleter_type> && not std::is_pointer_v<deleter_type>)
    :   base_type{t}
    {}

    constexpr explicit indirect_value(T* t, copier_type c) noexcept(std::is_nothrow_move_constructible_v<copier_type>&&
                                                                    std::is_nothrow_default_constructible_v<deleter_type>)
        requires(std::is_move_constructible_v<copier_type> &&
                 std::is_default_constructible_v<deleter_type> && not std::is_pointer_v<deleter_type>)
    :   base_type{t, std::move(c)}
    {}

    constexpr explicit indirect_value(T* t, copier_type c, deleter_type d) noexcept(std::is_nothrow_move_constructible_v<copier_type>&&
                                                                                    std::is_nothrow_move_constructible_v<deleter_type>)
        requires(std::is_move_constructible_v<copier_type> && std::is_move_constructible_v<deleter_type>)
    : base_type{ t, std::move(c), std::move(d) }
    {}

    constexpr ~indirect_value() { reset(); }

    /// Copy constructor.  
    /// \pre IsComplete<T> is false or std::is_copy_constructible_v<T> is true
    constexpr indirect_value(indirect_value const& i) requires (!meta::concepts::IsComplete<T> or std::is_copy_constructible_v<T>)
    :   base_type(i)
    {
        this->mValue = i.make_raw_copy();
    }

    /// Move constructor.  
    constexpr indirect_value(indirect_value&& i) noexcept(std::is_nothrow_move_constructible_v<copier_type> &&
                                                          std::is_nothrow_move_constructible_v<deleter_type>) 
    :   base_type(std::move(i))
    {}

    /// Copy assignment.
    /// \pre IsComplete<T> is false or std::is_copy_constructible_v<T> is true
    constexpr indirect_value& operator=(const indirect_value& i) requires (!meta::concepts::IsComplete<T> or std::is_copy_constructible_v<T>)
    {
        indirect_value temp(i);
        swap(temp);
        return *this;
    }

    constexpr indirect_value& operator=(indirect_value&& i) noexcept(std::is_nothrow_move_assignable_v<copier_type> &&
                                                                     std::is_nothrow_move_assignable_v<deleter_type>)
    {
        if (this != &i) 
        {
            reset();
            base_type::operator=(std::move(i));
        }
        return *this;
    }

#if (__cpp_explicit_this_parameter >= 202110)

    template<typename Self>
    [[nodiscard]] constexpr auto* operator->(this Self&& self) noexcept { return (this->mValue); }

    template<typename Self>
    [[nodiscard]] constexpr std::copy_cvref_t<Self, T>&& operator*(this Self&& self) noexcept { return *std::forward(self).mValue; }

    template<typename Self>
    [[nodiscard]] constexpr auto& value(this Self&& self) 
    {
        if (!this->mValue) throw bad_indirect_value_access();
        return *(this->mValue);
    }
#else

    [[nodiscard]] constexpr T* operator->() noexcept { return this->mValue; }

    [[nodiscard]] constexpr const T* operator->() const noexcept { return this->mValue; }

    [[nodiscard]] constexpr T& operator*() & noexcept { return *(this->mValue); }

    [[nodiscard]] constexpr const T& operator*() const& noexcept { return *(this->mValue); }

    [[nodiscard]] constexpr T&& operator*() && noexcept { return std::move(*(this->mValue)); }

    [[nodiscard]] constexpr const T&& operator*() const&& noexcept { return std::move(*(this->mValue)); }

    [[nodiscard]] constexpr T& value() & 
    {
        if (!this->mValue) throw bad_indirect_value_access();
        return *(this->mValue);
    }

    [[nodiscard]] constexpr T&& value() &&
    {
        if (!this->mValue) throw bad_indirect_value_access();
        return std::move(*(this->mValue));
    }

    [[nodiscard]] constexpr const T& value() const&
    {
        if (!this->mValue) throw bad_indirect_value_access();
        return *(this->mValue);
    }

    [[nodiscard]] constexpr const T&& value() const&&
    {
        if (!this->mValue) throw bad_indirect_value_access();
        return std::move(*(this->mValue));
    }
#endif // (__cpp_explicit_this_parameter >= 202110)

    explicit constexpr operator bool() const noexcept { return this->mValue != nullptr; }

    constexpr bool has_value() const noexcept { return this->mValue != nullptr; }

    constexpr copier_type& get_copier() noexcept { return this->getC(); }

    constexpr const copier_type& get_copier() const noexcept { return this->getC(); }

    constexpr deleter_type& get_deleter() noexcept { return this->getD(); }

    constexpr const deleter_type& get_deleter() const noexcept { return this->getD(); }

    constexpr void swap(indirect_value& rhs) noexcept(std::is_nothrow_swappable_v<base_type>)
    {
        this->base_type::swap(static_cast<base_type&>(rhs));
    }

    friend void swap(indirect_value& lhs, indirect_value& rhs) noexcept(noexcept(lhs.swap(rhs)))
        requires std::is_swappable_v<copier_type> && std::is_swappable_v<deleter_type>
    {
        lhs.swap(rhs);
    }
private:

    constexpr T* make_raw_copy() const { return this->mValue ? this->getC()(*(this->mValue)) : nullptr; }

    constexpr void reset() noexcept 
    {
        if (has_value()) 
        {
            this->getD()(exchange(this->mValue, nullptr));
        }
    }
};

template <class T>
indirect_value(T*)->indirect_value<T>;

template <class T, class... Ts>
constexpr indirect_value<T> make_indirect_value(Ts&&... ts) 
{
    return indirect_value<T>(std::in_place_t{}, std::forward<Ts>(ts)...);
}

template <class T, class A = std::allocator<T>, class... Ts>
constexpr auto allocate_indirect_value(std::allocator_arg_t, A& a, Ts&&... ts)
{
    auto* u = detail::allocate_object<T>(a, std::forward<Ts>(ts)...);
    try {
        return indirect_value<T, detail::allocator_copy<T, A>, detail::allocator_delete<T, A>>(u, { a }, { a });
    }
    catch (...) {
        detail::deallocate_object(a, u);
        throw;
    }
}

} // namespace morpheus::memory