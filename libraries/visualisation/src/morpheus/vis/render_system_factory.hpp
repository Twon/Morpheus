#pragma once

#include "morpheus/application/po/adapters/enum.hpp"
#include <morpheus/core/base/platform.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <morpheus/gfx/metal/render_system.hpp>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_WINDOWS)
    #include <morpheus/gfx/d3d12/render_system.hpp>
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

#include <morpheus/gfx/gl4/traits.hpp>
#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/vulkan/render_system.hpp>

#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana.hpp>

#include <boost/program_options/options_description.hpp>

#include <cstdint>
#include <type_traits>

namespace morpheus::vis
{

/// \enum API
///     Enumerate type describing the underlying graphics API for available render systems.
enum API : std::uint32_t
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
    RenderSystemFactory();
    ///@}

    /// Register program options
    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        options.add_options()("render-system", po::value(&mActiveApi)->default_value(mActiveApi), "The rendering system to instantiate.");
    }

private:

    /// Returns a map of the available rendering systems to their respective underlying graphics APIs.
    ///
    static constexpr auto availableAPIs()
    {
        namespace hana = boost::hana;
        return hana::make_map(
#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
            hana::make_pair(RenderSystemType<API::Metal>, hana::type_c<gfx::metal::RenderSystem>),
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_WINDOWS)
            hana::make_pair(RenderSystemType<API::D3D12>, hana::type_c<gfx::d3d12::RenderSystem>),
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
            hana::make_pair(RenderSystemType<API::OpenGL4>, hana::type_c<gfx::gl4::RenderSystem<gfx::gl4::GL4Traits>>),
            hana::make_pair(RenderSystemType<API::Vulkan>, hana::type_c<gfx::vulkan::RenderSystem>)
        );
    }

    //using APIMap = std::invoke_result_t<decltype(&RenderSystemFactory::availableAPIs)()>;

    //constexpr static auto renderSystemAPIs = availableAPIs();

    API mActiveApi = Vulkan;
};

} // namespace morpheus::vis
