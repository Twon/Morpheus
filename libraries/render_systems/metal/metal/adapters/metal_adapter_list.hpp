#pragma once

#include <core/platform.hpp>

namespace morpheus::gfx
{

/*! \class adapter_list

 */
class MORPHEUSCORE_EXPORT adapter_list {
public:

    class iterator {
    public:
        iterator() {}
    };

    adapter_list() {}
    
    iterator begin() { return iterator(); }
    iterator end() { return iterator(); }

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
    adapter_list(
        const std::uint32_t width,
        const std::uint32_t height,
        const std::uint32_t colourDepth
    );
    ///@}



    //! The width in pixels of the render target.
    std::uint32_t width() const noexcept { return mWidth; }

    //! The height in pixels of the render target.
    std::uint32_t height() const noexcept { return mHeight; }

    //! The colour depth of the pixels of the render target.
    std::uint32_t colout_depth() const noexcept { return mColourDepth; }

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the render target.
    const std::uint32_t mWidth = 0;
    //! The height in pixels of the render target.
    const std::uint32_t mHeight = 0;
    //! The colour depth of the pixels of the render target.
    const std::uint32_t mColourDepth = 0;
    ///@}
};

} // namespace morpheus::gfx
