#pragma once

#include <core/base/platform.hpp>
#include <indirect_value.h>

namespace morpheus::gfx::metal
{

/*! \class Adapter
        Describes an available graphic devices on the target platform.
 */
class Adapter {
public:
    /// \name Life cycle
    ///@{
    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
        \param[in] height
             The height in pixels of the render target.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    Adapter(
        const std::uint32_t width,
        const std::uint32_t height,
        const std::uint32_t colourDepth
    );
    ///@}

    Adapter();
    Adapter(Adapter&& rhs) noexcept;
    Adapter(const Adapter& rhs);
    Adapter& operator=(Adapter&& rhs) noexcept;
    Adapter& operator=(const Adapter& rhs);
    ~Adapter();
private:
    class Implementation;

    /// \name Data Members
    ///@{
    isocpp_p1950::indirect_value<Implementation> mImpl;
    ///@}
};

} // namespace morpheus::gfx::metal
