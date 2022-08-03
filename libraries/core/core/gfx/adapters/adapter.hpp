#pragma once

#include <core/platform.hpp>

#include <compare>
#include <concepts>

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
        const IdType adapterId
    )
    :   mAdapterId(adapterId)
    {
    }
    ///@}

    IdType const& getId() const noexcept { return mAdapterId; }

    [[nodiscard]] constexpr auto operator<=>(Adapter const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    IdType mAdapterId;
    ///@}
};

} // namespace morpheus::gfx
