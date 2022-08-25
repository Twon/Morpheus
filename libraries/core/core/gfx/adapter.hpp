#pragma once

#include <core/base/platform.hpp>

#include <compare>
#include <concepts>
#include <string>
#include <string_view>

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
    constexpr Adapter() noexcept = default;

    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
     */
    Adapter(
        const IdType adapterId,
        const std::string_view name
    )
    :   mAdapterId(adapterId)
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
