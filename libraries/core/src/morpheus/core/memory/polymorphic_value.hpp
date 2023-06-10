#pragma once

#include "morpheus/core/memory/copier_traits.hpp"
#include "morpheus/core/memory/default_copy.hpp"
#include "morpheus/core/memory/indirect_value.hpp"

#include <exception>
#include <memory>
#include <utility>

namespace morpheus::memory
{

/// \class bad_polymorphic_value_construction
///    Objects of type bad_polymorphic_value_construction are thrown to report invalid construction of a
///    polymorphic_value.
class bad_polymorphic_value_construction : public std::exception
{
public:
    bad_polymorphic_value_construction() noexcept = default;

    /// Ruturns an explanatory string.
    /// \return Return an implementation defined null terminated byte string.
    const char* what() const noexcept override;
};

namespace detail
{

/// \struct control_block_deleter
///     Specialiation of a deleter that uses a control blocks in built destory method to clean up resources used
///     to hold the control block.
struct control_block_deleter
{
    template <class T>
    constexpr void operator()(T* t) const noexcept
    {
        if (t != nullptr) {
            t->destroy();
        }
    }
};

/// \stuct control_block_copier
///    Specialisation of a copier that uses a control block to clone a copied control block.
struct control_block_copier
{
    /// The deleter type to be used to deallocate objects created by the copier.
    using deleter_type = control_block_deleter;

    template <class T>
    constexpr T* operator()(T const& t) const
    {
        return t.clone();
    }
};

/// \struct control_block
///     Control blocks are used within polymorphic values to specify how to construct the internal type when copying
///     for construction and assignment operations.  Type erasure is used here so subclasses can specify how to copy
///     but also where to allocate memory from.  This allows for instance subclasses to be derived which use allocator
///     or other memory resources from which to allocate from when cloning objects and other control blocks.
/// \tparam The underlying polymorphic type the control block creates.
template <class T>
struct control_block
{
    // using ControlBlockValue =
    //     indirect_value<detail::control_block<T>, detail::control_block_copier, detail::control_block_deleter>;

    constexpr virtual ~control_block() = default;

    // constexpr virtual ControlBlockValue clone() const = 0;

    constexpr virtual T* ptr() = 0;

    constexpr virtual void destroy() noexcept { delete this; }
};

/// \class  direct_control_block
/// \tparam T The underlying polymorphic type.
template <typename T>
class direct_control_block : public control_block<T>
{
public:
    using ControlBlockValue = typename control_block<T>::ControlBlockValue;

    template <typename... Ts>
    constexpr explicit direct_control_block(Ts&&... ts)
    : mStorage(std::forward<Ts>(ts)...)
    {}

    // constexpr ControlBlockValue clone() const override
    // {
    //     return make_indirect_value<direct_control_block<T>>(mStorage);
    // }

private:
    T mStorage;
};

} // namespace detail

/// \class polymorphic_value
///     Implements P0201r6, a polymorphic value type for C++.
/// \tparam T The underlying polymorphic type.
template<typename T>
class polymorphic_value
{
public:
    /// The base type of the underlying polymorphic hierarchy suported as an element in polymorpic value.
    using element_type = T;

    /// \defgroup Constructors
    ///@{
    /// Constructs an empty polymorphic value.
    constexpr polymorphic_value() noexcept = default;

    /// Allows explicit construction from a nullptr.
    constexpr polymorphic_value(nullptr_t) noexcept {}

    /// Copy constuction.
    constexpr polymorphic_value(const polymorphic_value& p) {}

    /// Move construction.
    constexpr polymorphic_value(polymorphic_value&& p) noexcept {}

    template <class U>
    constexpr explicit polymorphic_value(U&& u)
    {}

    template <class U, class C = default_copy<U>, class D = typename copier_traits<C>::deleter_type>
    constexpr explicit polymorphic_value(U* p, C c = C(), D d = D()) noexcept(
        std::is_nothrow_move_constructible_v<C>&& std::is_nothrow_move_constructible_v<D>)
    {}

    template <class U>
    constexpr explicit polymorphic_value(const polymorphic_value<U>& p);

    template <class U>
    constexpr explicit polymorphic_value(polymorphic_value<U>&& p);

    template <class U,
              //   class V = std::enable_if_t<std::is_convertible<std::decay_t<U>*, T*>::value &&
              //                              !is_polymorphic_value<std::decay_t<U>>::value>,
              class... Ts>
    constexpr explicit polymorphic_value(std::in_place_type_t<U>, Ts&&... ts);

    ///@}

    // Destructor
    constexpr ~polymorphic_value() = default;

    // Assignment
    constexpr polymorphic_value& operator=(const polymorphic_value& p);
    constexpr polymorphic_value& operator=(polymorphic_value&& p) noexcept;

    // Observers
#if (__cpp_explicit_this_parameter >= 202110L)

    [[nodiscard]] constexpr auto* operator->(this Self&& self) noexcept { return (this->mValue); }

    /// Dereferences pointer to the managed object.
    template <typename Self>
    [[nodiscard]] constexpr std::copy_cvref_t<Self, T>&& operator*(this Self&& self) noexcept
    {
        return *std::forward(self).mValue;
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

#endif // (__cpp_explicit_this_parameter >= 202110)

    /// Checks whether *this contains a value.
    explicit constexpr operator bool() const noexcept { return this->mValue != nullptr; }

    /// Checks whether *this contains a value.
    constexpr bool has_value() const noexcept { return this->mValue != nullptr; }

    // Modifiers
    constexpr void swap(polymorphic_value& rhs) noexcept
    {
        using std::swap;
        swap(mValue, rhs.mValue);
        swap(mControlBlock, rhs.mControlBlock);
    }

private:
    using ControlBlock = indirect_value<detail::control_block<element_type>, detail::control_block_copier,
                                        detail::control_block_deleter>;

    T* mValue = nullptr;
    ControlBlock mControlBlock;
};

} // namespace morpheus::memory