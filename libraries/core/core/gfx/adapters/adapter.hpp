#pragma once

#include <core/platform.hpp>

#if (MORPHEUSCORE_COMPILER_IS_MSVC)
#pragma warning( push )  
#pragma warning( disable : 4251 ) // 'foo' needs to have dll-interface to be used by clients of class 'bar'
#endif

namespace morpheus::gfx
{

/*! \class adapter
        Describes an available graphic devices on the target platform.
 */
class MORPHEUSCORE_EXPORT adapter {
public:
    /// \name Life cycle
    ///@{
    adapter() = default;

    /*! Constructs a render target with the specified parameters.
        \param[in] width
             The width in pixels of the render target.
        \param[in] height
             The height in pixels of the render target.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    adapter(
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
    std::uint32_t colour_depth() const noexcept { return mColourDepth; }

private:
    /// \name Data Members
    ///@{
    //! The width in pixels of the render target.
    std::uint32_t mWidth = 0;
    //! The height in pixels of the render target.
    std::uint32_t mHeight = 0;
    //! The colour depth of the pixels of the render target.
    std::uint32_t mColourDepth = 0;
    ///@}
};

} // namespace morpheus::gfx


#if (MORPHEUSCORE_COMPILER_IS_MSVC)
#pragma warning( pop )   
#endif