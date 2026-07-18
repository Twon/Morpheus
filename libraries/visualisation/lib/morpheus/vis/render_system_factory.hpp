#pragma once

#include "morpheus/application/po/adapters/enum.hpp"
#include <morpheus/core/base/platform.hpp>

#if (MORPHEUS_RENDER_SYSTEM_DIRECT_X12)
    #include <morpheus/gfx/d3d12/render_system.hpp>
#endif // #if (MORPHEUS_RENDER_SYSTEM_DIRECT_X12)

#if (MORPHEUS_RENDER_SYSTEM_METAL)
    #include <morpheus/gfx/metal/render_system.hpp>
#endif // #if (MORPHEUS_RENDER_SYSTEM_METAL)

#if (MORPHEUS_RENDER_SYSTEM_OPENGL4)
    #include <morpheus/gfx/gl4/render_system.hpp>
    #include <morpheus/gfx/gl4/traits.hpp>
#endif // #if (MORPHEUS_RENDER_SYSTEM_OPENGL4)

#if (MORPHEUS_RENDER_SYSTEM_VULKAN)
    #include <morpheus/gfx/vulkan/render_system.hpp>
#endif // #if (MORPHEUS_RENDER_SYSTEM_VULKAN)

#include <boost/hana.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/tuple.hpp>

#include <cstdint>
#include <type_traits>

namespace boost::program_options
{
class options_description;
}

namespace morpheus::vis
{

/// \enum API
///     Enumerate type describing the underlying graphics API for available render systems.
enum class API : std::uint32_t
{
    D3D12,
    Metal,
    OpenGL4,
    Vulkan
};

/// \var RenderSystemType
///     Template variable taking a non-type template parameter which is an integral type describing the render systems
///     underlying API.
template <auto Type>
constexpr auto RenderSystemType = boost::hana::type_c<boost::hana::integral_constant<std::remove_const_t<decltype(Type)>, Type>>;

/// \class RenderSystemFactory
///     The render system factory manages the available render systems for a target system.
///     Supported render systems can be queried and specific type can be instantiated to
///     render visualalisation with.
class RenderSystemFactory
{
public:
    /// \name Life cycle
    ///@{
    /*!

     */
    RenderSystemFactory() = default;
    ///@}

    /// Register program options
    void addOptions(boost::program_options::options_description& options);

    auto getActiveAPI() const -> API { return mActiveApi; }

private:
    /// Returns a map of the available rendering systems to their respective underlying graphics APIs.
    ///
    static constexpr auto availableAPIs()
    {
        namespace hana = boost::hana;

        struct NullRenderSystemAPI
        {};
        constexpr auto map = hana::make_map(hana::make_pair(hana::type_c<NullRenderSystemAPI>, hana::type_c<void>)
#if (MORPHEUS_RENDER_SYSTEM_METAL)
                                                ,
                                            hana::make_pair(RenderSystemType<API::Metal>, hana::type_c<gfx::metal::RenderSystem>)
#endif
#if (MORPHEUS_RENDER_SYSTEM_DIRECT_X12)
                                                ,
                                            hana::make_pair(RenderSystemType<API::D3D12>, hana::type_c<gfx::d3d12::RenderSystem>)
#endif
#if (MORPHEUS_RENDER_SYSTEM_OPENGL4)
                                                ,
                                            hana::make_pair(RenderSystemType<API::OpenGL4>, hana::type_c<gfx::gl4::RenderSystem<gfx::gl4::GL4Traits>>)
#endif
#if (MORPHEUS_RENDER_SYSTEM_VULKAN)
                                                ,
                                            hana::make_pair(RenderSystemType<API::Vulkan>, hana::type_c<gfx::vulkan::RenderSystem>)
#endif
        );

        return hana::erase_key(map, hana::type_c<NullRenderSystemAPI>);
    }

    // using APIMap = std::invoke_result_t<decltype(&RenderSystemFactory::availableAPIs)() >;

    // constexpr static auto renderSystemAPIs = availableAPIs();

    API mActiveApi = API::Vulkan;
};

} // namespace morpheus::vis
