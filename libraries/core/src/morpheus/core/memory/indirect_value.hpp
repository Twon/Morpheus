#pragma once

#include "morpheus/core/base/compiler.hpp"
#include "morpheus/core/conformance/version.hpp"
#include "morpheus/core/memory/copier_traits.hpp"
#include "morpheus/core/memory/default_copy.hpp"
#include "morpheus/core/meta/concepts/complete.hpp"
#include "morpheus/core/meta/concepts/hashable.hpp"

#include <boost/type_traits/copy_cv_ref.hpp>

#include <concepts>
#include <exception>
#include <memory>
#include <type_traits>
#include <utility>

namespace morpheus::memory
{

/// \class bad_indirect_value_access
///     Exception type thrown upon a accessing an indirect_value with no underlying value assigned.
class bad_indirect_value_access : public std::exception
{
public:
    /// Message describing the error.
    const char* what() const noexcept override { return "bad_indirect_value_access"; }
};

namespace detail
{

template <typename T, typename A, typename... Args>
constexpr T* allocate_object(A& a, Args&&... args)
{
    using t_allocator = typename std::allocator_traits<std::remove_cv_t<A>>::template rebind_alloc<T>;
    using t_traits = std::allocator_traits<t_allocator>;
    t_allocator t_alloc(a);
    T* mem = t_traits::allocate(t_alloc, 1);
    try {
        t_traits::construct(t_alloc, mem, std::forward<Args>(args)...);
        return mem;
    }
    catch (...) {
        t_traits::deallocate(t_alloc, mem, 1);
        throw;
    }
}

template <typename T, typename A>
constexpr void deallocate_object(A& a, T* p)
{
    using t_allocator = typename std::allocator_traits<std::remove_cv_t<A>>::template rebind_alloc<T>;
    using t_traits = std::allocator_traits<t_allocator>;
    t_allocator t_alloc(a);
    t_traits::destroy(t_alloc, p);
    t_traits::deallocate(t_alloc, p, 1);
}

/// \struct allocator_delete
///     Deleter type specialised for use with allocator types.
template <class A>
struct allocator_delete
{
    using value_type = typename A::value_type;

    A alloc;

    /// Construct with an allocator.
    constexpr allocator_delete(A& a)
    : alloc(a)
    {}

    /// Delete the input via the underlying allocator.
    constexpr void operator()(value_type* ptr) const noexcept
    {
        static_assert(0 < sizeof(value_type), "can't delete an incomplete type");
        detail::deallocate_object(alloc, ptr);
    }
};

/// \struct allocator_copy
///     Copier type specialised for use with allocator types.
template <class A>
struct allocator_copy
{
    /// The associated deleter to be used with this copier.
    using deleter_type = allocator_delete<A>;

    using value_type = typename A::value_type;

    A alloc;

    /// Construct with an allocator.
    constexpr allocator_copy(A& a) : alloc(a) {}

    /// Create a copy of the input via the underlying allocator.
    constexpr value_type* operator()(value_type const& t) const { return detail::allocate_object<value_type>(alloc, t); }
};

/// \struct exchange_on_move_ptr
///     Thin wrapper for a pointer to ensure moving of pointers results in a exchange with nullptr.  Use ensures
///     containing classes can rely on the rule of zero for special member functions.
template <typename T>
struct exchange_on_move_ptr
{
    /// Constructs an empty exchange_on_move_ptr.
    constexpr exchange_on_move_ptr() noexcept = default;

    /// Initialise the underlying pointer from the input.
    constexpr exchange_on_move_ptr(T* p) noexcept : ptr(p) {}

    /// Default copy construction of the underlying pointer.
    constexpr exchange_on_move_ptr(exchange_on_move_ptr const&) noexcept = default;

    /// Move construction, exchanges the underlying pointers.
    /// \note Resulting right hand side is null after the move.
    constexpr exchange_on_move_ptr(exchange_on_move_ptr&& rhs) noexcept : ptr(std::exchange(rhs.ptr, nullptr)) {}

    /// Default copy assignment of the underlying pointer.
    constexpr exchange_on_move_ptr& operator=(exchange_on_move_ptr const&) noexcept = default;

    /// Move assignment, exchanges the underlying pointers.
    /// \note Resulting right hand side is null after the move.
    constexpr exchange_on_move_ptr& operator=(exchange_on_move_ptr&& rhs) noexcept
    {
        ptr = std::exchange(rhs.ptr, nullptr);
        return *this;
    }

    /// Allows for copy-assignment from a raw pointer.
    constexpr exchange_on_move_ptr& operator=(T* p) noexcept
    {
        ptr = p;
        return *this;
    }

    /// Implicit conversion to underlying raw pointer type.
    constexpr explicit(false) operator T*() const noexcept { return ptr; }

    /// Allows for exchanging with any input pointer type.
    friend T* exchange(exchange_on_move_ptr& lhs, auto rhs) { return std::exchange(lhs.ptr, rhs); }

    T* ptr = nullptr; ///< Underlying pointer to be exchanged.
};

template <typename T, typename C, typename D>
struct indirect_value_base;

/// \struct indirect_value_base<T, CD, CD>
///     We must specialise to handle the case where copier and deleter are the same object and have no size.  In this
///     case this we have [[no_unique_address]] pointing to two objects of the same type which is not allowed by the
///     standard.  To support this we specialises away the unnecessary duplication of the object to avoid unnecessary
///     storage and in-doing so resolve the any issues around use of [[no_unique_address]]:
///     https://en.cppreference.com/w/cpp/language/attributes/no_unique_address
/// \tparam T The underlying value type
/// \tparam CD The combined copier and deleter object
template <typename T, typename CD>
struct indirect_value_base<T, CD, CD>
{
    exchange_on_move_ptr<T> mValue; ///< The indirectly owned value.

#if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    [[msvc::no_unique_address]] CD mCopierDeleterCombined; ///< Functor customising the copying and deleting of the undelrying value.
#else
    [[no_unique_address]] CD mCopierDeleterCombined; ///< Functor customising the copying and deleting of the undelrying value.
#endif

    /// Default constructor.
    constexpr indirect_value_base() = default;

    /// Constructs an indirect_value_base which owns takes ownership of the input t.
    /// \param[in] t Pointer to the underlying value to be owned.
    /// \param[in] cd Combined copier and deleter functor to customise how the underlying value is copied and deleted.
    constexpr explicit indirect_value_base(T* t, CD cd = CD())
    : mValue(t)
    , mCopierDeleterCombined(std::move(cd))
    {}

#if (__cpp_explicit_this_parameter >= 202110L)
    /// Access the copier.
    template <typename Self>
    [[nodiscard]] constexpr auto getC(this Self&& self) -> boost::copy_cv_ref_t<CD, decltype(self)>
    {
        return std::forward_like<decltype(self)>(self.mCopierDeleterCombined);
    }

    /// Access the deleter.
    template <typename Self>
    [[nodiscard]] constexpr auto getD(this Self&& self) -> boost::copy_cv_ref_t<CD, decltype(self)>
    {
        return std::forward_like<decltype(self)>(self.mCopierDeleterCombined);
    }
#else
    /// Access the copier.
    [[nodiscard]] constexpr auto& getC() & { return mCopierDeleterCombined; }

    /// Access the copier.
    [[nodiscard]] constexpr auto const& getC() const& { return mCopierDeleterCombined; }

    /// Access the copier.
    [[nodiscard]] constexpr auto&& getC() && { return std::move(mCopierDeleterCombined); }

    /// Access the copier.
    [[nodiscard]] constexpr auto const&& getC() const&& { return std::move(mCopierDeleterCombined); }

    /// Access the deleter.
    [[nodiscard]] constexpr auto& getD() & { return mCopierDeleterCombined; }

    /// Access the deleter.
    [[nodiscard]] constexpr auto const& getD() const& { return mCopierDeleterCombined; }

    /// Access the deleter.
    [[nodiscard]] constexpr auto&& getD() && { return std::move(mCopierDeleterCombined); }

    /// Access the deleter.
    [[nodiscard]] constexpr auto const&& getD() const&& { return std::move(mCopierDeleterCombined); }
#endif

    /// Swaps the indirectly owned objects.
    constexpr void swap(indirect_value_base& rhs) noexcept(std::is_nothrow_swappable_v<CD>)
    {
        using std::swap;
        swap(mValue, rhs.mValue);
        swap(mCopierDeleterCombined, rhs.mCopierDeleterCombined);
    }
};

/// \struct indirect_value_base
///     The default case for indirect value is the case where copier and deleter are the different object.  In many cases
///     these will have no size and are thus marked [[no_unique_address]] to avoid any storage requirements
/// \tparam T The underlying value type.
/// \tparam C The copier object.
/// \tparam D The deleter object.
template <typename T, typename C, typename D>
struct indirect_value_base
{
    exchange_on_move_ptr<T> mValue; ///< The indirectly owned value.

#if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
    [[msvc::no_unique_address]] C mCopier;  ///< The copier functor to customise how the underlying value is copied.
    [[msvc::no_unique_address]] D mDeleter; ///< The deleter functor to customise how the underlying value is deleted.
#else
    [[no_unique_address]] C mCopier;  ///< The copier functor to customise how the underlying value is copied.
    [[no_unique_address]] D mDeleter; ///< The deleter functor to customise how the underlying value is deleted.
#endif

    /// Default constructor.
    /// \note Default constructor is noexcept if copier and deleter are both nothrow default constructible.
    //constexpr indirect_value_base() noexcept(std::is_nothrow_default_constructible_v<C> && std::is_nothrow_default_constructible_v<D>) = default;
    constexpr indirect_value_base() = default;

    constexpr explicit indirect_value_base(T* t, C c = C(), D d = D())
    : mValue(t)
    , mCopier(std::move(c))
    , mDeleter(std::move(d))
    {}

#if (__cpp_explicit_this_parameter >= 202110L)
    /// Access the copier.
    template <typename Self>
    [[nodiscard]] constexpr auto getC(this Self&& self) -> boost::copy_cv_ref_t<C, decltype(self)>
    {
        return std::forward_like<decltype(self)>(self.mCopier);
    }

    /// Access the deleter.
    template <typename Self>
    [[nodiscard]] constexpr auto getD(this Self&& self) -> boost::copy_cv_ref_t<D, decltype(self)>
    {
        return std::forward_like<decltype(self)>(self.mDeleter);
    }
#else
    /// Access the copier.
    [[nodiscard]] constexpr auto& getC() & { return mCopier; }

    /// Access the copier.
    [[nodiscard]] constexpr auto const& getC() const& { return mCopier; }

    /// Access the copier.
    [[nodiscard]] constexpr auto&& getC() && { return std::move(mCopier); }

    /// Access the copier.
    [[nodiscard]] constexpr auto const&& getC() const&& { return std::move(mCopier); }

    /// Access the deleter.
    [[nodiscard]] constexpr auto& getD() & { return mDeleter; }

    /// Access the deleter.
    [[nodiscard]] constexpr auto const& getD() const& { return mDeleter; }

    /// Access the deleter.
    [[nodiscard]] constexpr auto&& getD() && { return std::move(mDeleter); }

    /// Access the deleter.
    [[nodiscard]] constexpr auto const&& getD() const&& { return std::move(mDeleter); }
#endif

    /// Swaps the indirectly owned objects.
    constexpr void swap(indirect_value_base& rhs) noexcept(std::is_nothrow_swappable_v<C>&& std::is_nothrow_swappable_v<D>)
    {
        using std::swap;
        swap(mValue, rhs.mValue);
        swap(mCopier, rhs.mCopier);
        swap(mDeleter, rhs.mDeleter);
    }
};

} // namespace detail

/// \class indirect_value
///     Implements P1950R2, a free-store-allocated value type for C++
/// \tparam T The underlying value type.
/// \tparam Copier The copier functor to customise how the underlying value is copied.
/// \tparam Deleter The deleter functor to customise how the underlying value is deleted.
// template <typename T, std::invocable<T const&> Copier = default_copy<T>, std::invocable<T*> Deleter = typename copier_traits<Copier>::deleter_type>
// requires std::same_as<std::invoke_result_t<Copier, T const&>, T*>
template <typename T, typename Copier = default_copy<T>, typename Deleter = typename copier_traits<Copier>::deleter_type>
class indirect_value : public detail::indirect_value_base<T, Copier, Deleter>
{
    using base_type = detail::indirect_value_base<T, Copier, Deleter>;

public:
    using value_type = T;         ///< Underlying value type
    using copier_type = Copier;   ///< Copier object customising copying of underlying value
    using deleter_type = Deleter; ///< Deleter object customising deleting of underlying value

    /// Constructs an empty indirect_value.
    constexpr indirect_value() noexcept(std::is_nothrow_default_constructible_v<copier_type>&& std::is_nothrow_default_constructible_v<deleter_type>) = default;

    /// Inplace construction of the indirect value.
    /// \note Conditionally enabled only when the input parameters match the requires parameter of the underlying types
    ///       constructors.
    /// \param[in] ts Forwarded parameters to underlying types constructor.
    template <class... Ts>
    requires(std::is_constructible_v<T, Ts...>)
    constexpr explicit indirect_value(std::in_place_t, Ts&&... ts) : base_type{new T(std::forward<Ts>(ts)...)}
    {}

    /// Constructs a indirect_value which owns takes ownership of the input t. The copier and deleter are default constructed.
    /// \note If t is null, creates an empty object.
    constexpr explicit indirect_value(T* t) noexcept(
        std::is_nothrow_default_constructible_v<copier_type>&& std::is_nothrow_default_constructible_v<deleter_type>)
    requires(std::is_default_constructible_v<copier_type> && not std::is_pointer_v<copier_type> && std::is_default_constructible_v<deleter_type> &&
             not std::is_pointer_v<deleter_type>)
    : base_type{t}
    {}

    /// Constructs a indirect_value which owns takes ownership of the input t. The copier is moved from c and deleter is default constructed.
    /// \note If t is null, creates an empty object.
    constexpr explicit indirect_value(T* t, copier_type c) noexcept(
        std::is_nothrow_move_constructible_v<copier_type>&& std::is_nothrow_default_constructible_v<deleter_type>)
    requires(std::is_move_constructible_v<copier_type> && std::is_default_constructible_v<deleter_type> && not std::is_pointer_v<deleter_type>)
    : base_type{t, std::move(c)}
    {}

    /// Constructs a indirect_value which owns takes ownership of the input t. The copier is moved from c and deleter is moved from d.
    /// \note If t is null, creates an empty object.
    constexpr explicit indirect_value(T* t, copier_type c, deleter_type d) noexcept(
        std::is_nothrow_move_constructible_v<copier_type>&& std::is_nothrow_move_constructible_v<deleter_type>)
    requires(std::is_move_constructible_v<copier_type> && std::is_move_constructible_v<deleter_type>)
    : base_type{t, std::move(c), std::move(d)}
    {}

    constexpr ~indirect_value() { reset(); }

    /// Copy constructor.
    /// \pre IsComplete<T> is false or std::is_copy_constructible_v<T> is true
    constexpr indirect_value(indirect_value const& i)
    // requires(!meta::concepts::IsComplete<T> or std::is_copy_constructible_v<T>)
    : base_type(i)
    {
        this->mValue = i.make_raw_copy();
    }

    /// Move constructor.
    constexpr indirect_value(indirect_value&& i) noexcept(
        std::is_nothrow_move_constructible_v<copier_type>&& std::is_nothrow_move_constructible_v<deleter_type>)
    : base_type(std::move(i))
    {}

    /// Copy assignment, assigns contents via the underlying copier
    /// \pre IsComplete<T> is false or std::is_copy_constructible_v<T> is true
    constexpr indirect_value& operator=(indirect_value const& i)
    //    requires(!meta::concepts::IsComplete<T> or std::is_copy_constructible_v<T>)
    {
        indirect_value temp(i);
        swap(temp);
        return *this;
    }

    /// Move assignment, assigns contents via moving from the right hand side to the left hand side.
    constexpr indirect_value&
    operator=(indirect_value&& i) noexcept(std::is_nothrow_move_assignable_v<copier_type>&& std::is_nothrow_move_assignable_v<deleter_type>)
    {
        if (this != &i) {
            reset();
            base_type::operator=(std::move(i));
        }
        return *this;
    }

#if (__cpp_explicit_this_parameter >= 202110L)

    /// Accesses the contained value.
    template <typename Self>
    [[nodiscard]] constexpr auto operator->(this Self&& self) noexcept -> boost::copy_cv_t<T*, decltype(self)>
    {
        return (self.mValue);
    }

    /// Dereferences pointer to the managed object.
    template <typename Self>
    [[nodiscard]] constexpr auto operator*(this Self&& self) noexcept -> boost::copy_cv_ref_t<T, decltype(self)>
    {
        return std::forward_like<decltype(self)>(*self.mValue);
    }

    /// If *this contains a value, returns a reference to the contained value. Otherwise, throws a bad_indirect_value_access exception.
    template <typename Self>
    [[nodiscard]] constexpr auto value(this Self&& self) -> boost::copy_cv_ref_t<T, decltype(self)>
    {
        if (!self.mValue)
            throw bad_indirect_value_access();
        return std::forward_like<decltype(self)>(*self.mValue);
    }
#else
    /// Accesses the contained value.
    [[nodiscard]] constexpr T* operator->() noexcept { return this->mValue; }

    /// Accesses the contained value.
    [[nodiscard]] constexpr const T* operator->() const noexcept { return this->mValue; }

    /// Dereferences pointer to the managed object.
    [[nodiscard]] constexpr T& operator*() & noexcept { return *(this->mValue); }

    /// Dereferences pointer to the managed object.
    [[nodiscard]] constexpr const T& operator*() const& noexcept { return *(this->mValue); }

    /// Dereferences pointer to the managed object.
    [[nodiscard]] constexpr T&& operator*() && noexcept { return std::move(*(this->mValue)); }

    /// Dereferences pointer to the managed object.
    [[nodiscard]] constexpr const T&& operator*() const&& noexcept { return std::move(*(this->mValue)); }

    /// If *this contains a value, returns a reference to the contained value. Otherwise, throws a bad_indirect_value_access exception.
    [[nodiscard]] constexpr T& value() &
    {
        if (!this->mValue)
            throw bad_indirect_value_access();
        return *(this->mValue);
    }

    /// If *this contains a value, returns a reference to the contained value. Otherwise, throws a bad_indirect_value_access exception.
    [[nodiscard]] constexpr T&& value() &&
    {
        if (!this->mValue)
            throw bad_indirect_value_access();
        return std::move(*(this->mValue));
    }

    /// If *this contains a value, returns a reference to the contained value. Otherwise, throws a bad_indirect_value_access exception.
    [[nodiscard]] constexpr const T& value() const&
    {
        if (!this->mValue)
            throw bad_indirect_value_access();
        return *(this->mValue);
    }

    /// If *this contains a value, returns a reference to the contained value. Otherwise, throws a bad_indirect_value_access exception.
    [[nodiscard]] constexpr const T&& value() const&&
    {
        if (!this->mValue)
            throw bad_indirect_value_access();
        return std::move(*(this->mValue));
    }
#endif // (__cpp_explicit_this_parameter >= 202110)

    /// Checks whether *this contains a value.
    explicit constexpr operator bool() const noexcept { return this->mValue != nullptr; }

    /// Checks whether *this contains a value.
    constexpr bool has_value() const noexcept { return this->mValue != nullptr; }

    /// Access the copier.
    constexpr copier_type& get_copier() noexcept { return this->getC(); }

    /// Access the copier.
    constexpr const copier_type& get_copier() const noexcept { return this->getC(); }

    /// Access the deleter.
    constexpr deleter_type& get_deleter() noexcept { return this->getD(); }

    /// Access the deleter.
    constexpr const deleter_type& get_deleter() const noexcept { return this->getD(); }

    /// Swaps the indirectly owned objects.
    constexpr void swap(indirect_value& rhs) noexcept(std::is_nothrow_swappable_v<base_type>) { this->base_type::swap(static_cast<base_type&>(rhs)); }

    /// Specialises the std::swap algorithm.
    friend void swap(indirect_value& lhs, indirect_value& rhs) noexcept(noexcept(lhs.swap(rhs)))
    requires std::is_swappable_v<copier_type> && std::is_swappable_v<deleter_type>
    {
        lhs.swap(rhs);
    }

private:
    constexpr T* make_raw_copy() const { return this->mValue ? this->getC()(*(this->mValue)) : nullptr; }

    constexpr void reset() noexcept
    {
        if (has_value()) {
            this->getD()(exchange(this->mValue, nullptr));
        }
    }
};

template <class T>
indirect_value(T*) -> indirect_value<T>;

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
        return indirect_value<T, detail::allocator_copy<A>, detail::allocator_delete<A>>(u, {a}, {a});
    }
    catch (...) {
        detail::deallocate_object(a, u);
        throw;
    }
}

} // namespace morpheus::memory

/// Specialisation of std::hash for morpheus::memory::indirect_value.
template <class T, class C, class D>
requires morpheus::meta::concepts::IsHashable<T>
struct std::hash<::morpheus::memory::indirect_value<T, C, D>>
{
    /// Computes the hash of the underlying value.
    /// \param key The indirect_value to compute the hash for.
    /// \return The hash of the underlying value, or 0 if the indirect_value is empty.
    /// \note noexcept if the underlying value type is noexcept hashable.
    constexpr std::size_t operator()(const ::morpheus::memory::indirect_value<T, C, D>& key) const
        noexcept(noexcept(std::hash<typename ::morpheus::memory::indirect_value<T, C, D>::value_type>{}(*key)))
    {
        return key ? std::hash<typename ::morpheus::memory::indirect_value<T, C, D>::value_type>{}(*key) : 0;
    }
};
