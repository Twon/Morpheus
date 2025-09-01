#pragma once

#include <morpheus/core/base/platform.hpp>

#if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)
    #include <morpheus/gfx/metal/render_system.hpp>
#elif (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <morpheus/gfx/d3d12/render_system.hpp>
#endif // #if (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_APPLE)

#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/gl4/traits.hpp>
#include <morpheus/gfx/vulkan/render_system.hpp>

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
    RenderSystemFactory() = default;
    ///@}

    /// Register program options
    void addOptions(boost::program_options::options_description& options);

    // boost::program_options::options_description& runTuiConfiguration();
    void runTuiConfiguration();

private:
    /// Returns a map of the available rendering systems to their respective underlying graphics APIs.
    ///
    static constexpr auto availableAPIs();

    // using APIMap = std::invoke_result_t<decltype(&RenderSystemFactory::availableAPIs)()>;

    // constexpr static auto renderSystemAPIs = availableAPIs();

    API mActiveApi = Vulkan;
};

} // namespace morpheus::vis
