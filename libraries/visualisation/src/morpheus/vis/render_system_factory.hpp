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
#include <type_traits>

namespace morpheus::gfx
{

/// \enum API
///     Enumerate type describing the underlying graphics API for avaiable render systems.
enum API : std::uint32_t
{
    D3D12,
    Metal,
    OpenGL4,
    Vulkan
};

/// \var RenderSystemType
///     Template variable taking a non-type template parameter which is an intergral type describing the a render systems
///     underlying API.
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

    /// Register program options
    void addOptions(boost::program_options::options_description& options)
    {
        namespace hana = boost::hana;
        hana::for_each(renderSystemAPIs)
    }

    //void register()

    /// Returns a map of the available rendering systems to their respective underlying graphics APIs.
    ///
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
    using APIMap = std::invoke_result_t<availableAPIs()>;

    constexpr static APIMap renderSystemAPIs = availableAPIs();
};

} // namespace morpheus::gfx
