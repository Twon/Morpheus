#pragma once

#include <morpheus/core/base/platform.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <morpheus/gfx/metal/render_system.hpp>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_WINDOWS)
    #include <morpheus/gfx/d3d12/render_system.hpp>
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/vulkan/render_system.hpp>

#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana.hpp>

#include <cstdint>

namespace morpheus::gfx
{

enum API : std::uint32_t
{
    D3D12,
    Metal,
    OpenGL4,
    Vulkan
};

template <auto Type>
constexpr auto RenderSystemType = boost::hana::type_c<boost::hana::integral_constant<std::remove_const_t<decltype(Type)>, Type>>;

/// \class RenderSystemFactory
///     The render system factory manages the available render systems for a target system.
///     Supported render systems can be queried and specfic type can be instantiated to
///     render visualalisation with.
class RenderSystemFactory
{
public:
    /// \name Life cycle
    ///@{
    /*!

     */
    RenderSystemFactory();
    ///@}

    //void register()

    static constexpr auto availableAPIs()
    {
        return boost::hana::make_map(
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
            boost::hana::make_pair(RenderSystemType<API::Metal>, boost::hana::type_c<metal::RenderSystem>)
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_WINDOWS)
            boost::hana::make_pair(RenderSystemType<API::D3D12>, boost::hana::type_c<d3d12::RenderSystem>),
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
            boost::hana::make_pair(RenderSystemType<API::OpenGL4>, boost::hana::type_c<gl4::RenderSystem>),
            boost::hana::make_pair(RenderSystemType<API::Vulkan>, boost::hana::type_c<vulkan::RenderSystem>)
        );
    }

private:
};

} // namespace morpheus::gfx
