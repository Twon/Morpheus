#pragma once

#include "morpheus/gfx/platform/vendor.hpp"

#include <compare>
#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::gfx
{

/// \class Adapter
///     Describes an available graphic adapter on the target platform.
///
template <std::regular IdType>
class Adapter
{
public:
    /// \name Life cycle
    ///@{
    /// Default construction an empty adapter.
    constexpr explicit Adapter() noexcept = default;

    /// Constructs an adapter from name and id.
    constexpr explicit Adapter(
        IdType adapterId,
        std::string_view const name,
        Vendor const vendor
    )   noexcept(noexcept(std::is_nothrow_move_assignable_v<IdType>))
    :   mAdapterId(adapterId)
    ,   mName(name)
    ,   mVendor(vendor)
    {
    }
    ///@}

    /// Access the adapter Id.
    [[nodiscard]] constexpr auto const& id() const noexcept { return mAdapterId; }

    /// Access the adapter name.
    [[nodiscard]] constexpr auto const& name() const noexcept { return mName; }

    /// Access the adapter vendor.
    [[nodiscard]] constexpr auto vendor() const noexcept { return mVendor; }

    /// Compare two adapter objects.
    [[nodiscard]] constexpr auto operator<=>(Adapter const& rhs) const noexcept -> std::strong_ordering = default;

private:
    /// \name Data Members
    ///@{
    IdType mAdapterId = {};
    std::string mName;
    Vendor mVendor = Vendor::Unknown;
    ///@}
};

} // namespace morpheus::gfx
