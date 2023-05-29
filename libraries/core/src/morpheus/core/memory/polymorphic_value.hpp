#pragma once

#include "morpheus/core/memory/copier_traits.hpp"
#include "morpheus/core/memory/default_copy.hpp"

#include <exception>
#include <memory>
#include <utility>

namespace morpheus::memory
{

/// \class bad_polymorphic_value_construction
///    Objects of type bad_polymorphic_value_construction are thrown to report invalid construction of a polymorphic_value.
class bad_polymorphic_value_construction : public std::exception
{
public:
    bad_polymorphic_value_construction() noexcept = default;

    /// Ruturns an explanatory string.
    /// \return Return an implementation defined null terminated byte string.
    const char* what() const noexcept override;
};

/// \class polymorphic_value
///     Implements P0201r6, a polymorphic value type for C++.
/// \tparam T The underlying polymorphic type.
template<typename T>
class polymorphic_value
{
public:
    /// The base type of the underlying polymorphic hierarchy suported as an element in polymorpic value.
    using element_type = T;

    /// Constructs an empty polymorphic value.
    constexpr polymorphic_value() noexcept {}

    constexpr polymorphic_value(nullptr_t) noexcept;

    template <class U>
    constexpr explicit polymorphic_value(U&& u);

    template <class U, class C = default_copy<U>, class D = typename copier_traits<C>::deleter_type>
    constexpr explicit polymorphic_value(U* p, C c = C(), D d = D());

    constexpr polymorphic_value(const polymorphic_value& p);

    template <class U>
    constexpr explicit polymorphic_value(const polymorphic_value<U>& p);

    constexpr polymorphic_value(polymorphic_value&& p) noexcept;

    template <class U>
    constexpr explicit polymorphic_value(polymorphic_value<U>&& p);

    // Destructor
    constexpr ~polymorphic_value();

    // Assignment
    constexpr polymorphic_value& operator=(const polymorphic_value& p);
    constexpr polymorphic_value& operator=(polymorphic_value&& p) noexcept;

    // Observers
    constexpr const T& operator*() const;
    constexpr T& operator*();
    constexpr const T* operator->() const;
    constexpr T* operator->();

    constexpr explicit operator bool() const noexcept { return false; }

    // Modifiers
    constexpr void swap(polymorphic_value& rhs) noexcept
    {
        using std::swap;
        // swap(mValue, rhs.mValue);
    }

private:
};

} // namespace morpheus::memory