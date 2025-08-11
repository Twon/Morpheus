#pragma once

#include <morpheus/core/memory/indirect_value.hpp>

#include <cstdint>

namespace morpheus::gfx::metal
{

/*! \class Adapter
        Describes an available graphic devices on the target platform.
 */
class Adapter
{
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
        std::uint32_t const width,
        std::uint32_t const height,
        std::uint32_t const colourDepth
    );
    ///@}

    Adapter();
    Adapter(Adapter&& rhs) noexcept;
    Adapter(Adapter const& rhs);
    Adapter& operator=(Adapter&& rhs) noexcept;
    Adapter& operator=(Adapter const& rhs);
    ~Adapter();

private:
    struct Implementation;

    /// \name Data Members
    ///@{
    memory::indirect_value<Implementation> mImpl;
    ///@}
};

} // namespace morpheus::gfx::metal
