#pragma once

#include "morpheus/core/memory/copier_traits.hpp"
#include "morpheus/core/memory/default_copy.hpp"
#include "morpheus/core/memory/indirect_value.hpp"

#include <exception>
#include <memory>
#include <type_traits>
#include <typeinfo>
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
    constexpr const char* what() const noexcept override { return "Dynamic and static type mismatch in polymorphic_value construction"; }
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
    using ControlBlockValue = indirect_value<detail::control_block<T>, detail::control_block_copier, detail::control_block_deleter>;

    constexpr virtual ~control_block() = default;

    [[nodiscard]] constexpr virtual control_block* clone() const = 0;

    [[nodiscard]] constexpr virtual T* ptr() noexcept = 0;

    [[nodiscard]] constexpr virtual T const* ptr() const noexcept = 0;

    constexpr virtual void destroy() noexcept { delete this; }
};

/// \class  direct_control_block
/// \tparam T The underlying base polymorphic type.
/// \tparam U The underlying derived polymorphic type.
template <typename T, typename U>
class direct_control_block : public control_block<T>
{
public:
    using ControlBlockValue = typename control_block<T>::ControlBlockValue;

    template <typename... Ts>
    constexpr explicit direct_control_block(Ts&&... ts)
    : mStorage(std::forward<Ts>(ts)...)
    {}

    [[nodiscard]] constexpr direct_control_block* clone() const override { return new direct_control_block<T, U>(mStorage); }

    [[nodiscard]] constexpr U* ptr() noexcept override { return &mStorage; };

    [[nodiscard]] constexpr U const* ptr() const noexcept override { return &mStorage; }

private:
    U mStorage;
};

template <typename T, typename U, typename C, typename D>
class pointer_control_block : public control_block<T>
{
public:
    using ControlBlockValue = typename control_block<T>::ControlBlockValue;

    constexpr explicit pointer_control_block(U* u, C c, D d)
    : mIndirect(u, std::move(c), std::move(d))
    {}

    [[nodiscard]] constexpr pointer_control_block* clone() const override { return new pointer_control_block(*this); }

    [[nodiscard]] constexpr T* ptr() noexcept override { return mIndirect.operator->(); }

    [[nodiscard]] constexpr T const* ptr() const noexcept override { return mIndirect.operator->(); }

private:
    indirect_value<U, C, D> mIndirect;
};

} // namespace detail

/// \class polymorphic_value
///     Implements P0201r6, a polymorphic value type for C++.
/// \tparam T The underlying polymorphic type.
template <typename T>
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
    constexpr explicit polymorphic_value(U* u, C c = C(), D d = D())

        requires std::is_convertible_v<U*, T*>
    {
        if (!u) {
            return;
        }

        if (std::is_same_v<D, std::default_delete<U>> and std::is_same_v<C, default_copy<U>> and typeid(*u) != typeid(U)) {
            throw bad_polymorphic_value_construction();
        }

        mValue = u;
        // mControlBlock = indirect_value<detail::control_block<element_type>, detail::control_block_copier, detail::control_block_deleter>(
        //     new detail::pointer_control_block<T, U, C, D>(u, std::move(c), std::move(d)));
    }

    template <class U>
    constexpr explicit polymorphic_value(const polymorphic_value<U>& p)
    {}

    template <class U>
    constexpr explicit polymorphic_value(polymorphic_value<U>&& p)
    {}

    template <class U,
              //   class V = std::enable_if_t<std::is_convertible<std::decay_t<U>*, T*>::value &&
              //                              !is_polymorphic_value<std::decay_t<U>>::value>,
              class... Ts>
    constexpr explicit polymorphic_value(std::in_place_type_t<U>, Ts&&... ts)
    : mControlBlock(new detail::direct_control_block<T, U>(std::forward<Ts>(ts)...))
    , mValue(mControlBlock->ptr())
    {}

    ///@}

    // Destructor
    constexpr ~polymorphic_value() = default;

    // Assignment
    constexpr polymorphic_value& operator=(const polymorphic_value& p)
    {
        // if (this != &p) {
        //     mControlBlock = p.mControlBlock;
        //     mValue = (mControlBlock) ? mValue = mControlBlock->ptr() : nullptr;
        // }
        return *this;
    }

    constexpr polymorphic_value& operator=(polymorphic_value&& p) noexcept = default;

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

    ControlBlock mControlBlock;
    T* mValue = nullptr;
};

//
// polymorphic_value creation
//
template <class T, class U = T, class... Ts>
constexpr polymorphic_value<T> make_polymorphic_value(Ts&&... ts)
{
    polymorphic_value<T> p;
    //   p.cb_ = std::unique_ptr<detail::direct_control_block<T, U>,
    //                           detail::control_block_deleter>(
    //       new detail::direct_control_block<T, U>(std::forward<Ts>(ts)...));
    //   p.ptr_ = p.cb_->ptr();
    return p;
}

template <class T, class U = T, class A = std::allocator<U>, class... Ts>
constexpr polymorphic_value<T> allocate_polymorphic_value(std::allocator_arg_t, A& a, Ts&&... ts)
{
    polymorphic_value<T> p;
    //   auto* u = detail::allocate_object<U>(a, std::forward<Ts>(ts)...);
    //   try {
    //     p.cb_ = std::unique_ptr<detail::allocated_pointer_control_block<T, U, A>,
    //                             detail::control_block_deleter>(
    //         detail::allocate_object<
    //             detail::allocated_pointer_control_block<T, U, A>>(a, u, a));
    //   } catch (...) {
    //     detail::deallocate_object(a, u);
    //     throw;
    //   }
    //   p.ptr_ = p.cb_->ptr();
    return p;
}

//
// non-member swap
//
template <class T>
constexpr void swap(polymorphic_value<T>& t, polymorphic_value<T>& u) noexcept
{
    t.swap(u);
}

} // namespace morpheus::memory