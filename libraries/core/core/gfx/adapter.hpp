#pragma once

#include <core/base/platform.hpp>

#include <compare>
#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::gfx
{

/*! \class adapter
        Describes an available graphic adapter on the target platform.
 */
template<std::regular IdType>
class Adapter {
public:
    /// \name Life cycle
    ///@{
    /// Default construction.
    constexpr Adapter() noexcept = default;

    /// Constructs an adapter from name and id.
    constexpr Adapter(
        IdType adapterId,
        std::string_view const name
    )   noexcept(noexcept(std::is_nothrow_move_assignable_v<IdType>))
    :    mAdapterId(adapterId)
    ,    mName(name)
    {
    }
    ///@}

    [[nodiscard]] constexpr auto const& getId() const noexcept { return mAdapterId; }
    [[nodiscard]] constexpr auto const& getName() const noexcept { return mName; }
    [[nodiscard]] constexpr auto operator<=>(Adapter const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    IdType mAdapterId; 
    std::string mName;
    ///@}
};

} // namespace morpheus::gfx
