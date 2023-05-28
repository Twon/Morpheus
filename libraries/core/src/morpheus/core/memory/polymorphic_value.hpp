#pragma once

#include <exception>

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

    explicit operator bool() const { return false; }

    constexpr void swap(polymorphic_value& rhs) noexcept
    {
        using std::swap;
        // swap(mValue, rhs.mValue);
    }

private:
};

} // namespace morpheus::memory