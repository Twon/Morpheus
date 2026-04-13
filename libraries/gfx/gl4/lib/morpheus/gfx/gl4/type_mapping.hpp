#pragma once

namespace morpheus::gfx::gl4
{

/*! \class TypeMapping
        Provides helper methods for mapping from native types to the underlying rendering API.
 */
class TypeMapping
{
public:
    /// \name Life cycle
    ///@{
    /*! Constructs a video mode with the specified parameters.
        \param[in] width
             The width in pixels of the video mode.
        \param[in] height
             The height in pixels of the video mode.
        \param[in] colourDepth
             The colour depth of the pixels of the render target.
     */
    TypeMapping(
        //       const std::uint32_t width,
        //       const std::uint32_t height,
        //       const std::uint32_t colourDepth
    );
    ///@}

private:
};

} // namespace morpheus::gfx::gl4
