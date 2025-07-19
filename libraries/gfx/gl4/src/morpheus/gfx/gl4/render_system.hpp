#pragma once

#include <morpheus/core/conformance/expected.hpp>
//#include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/platform/render_system.hpp>

#include <string_view>
#include <string>

namespace morpheus::gfx::gl4
{

/// \class RenderSystem
///     Rendering system abstraction based upon the OpenGL 4 graphics API.
/// \tparam T
///     The traits of the rendering system.
template <class T>
class RenderSystem : public gfx::RenderSystem
{
public:
    using Window = typename T::Window;

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    static [[nodiscard]] std::string_view getGraphicsApi() noexcept { return "Open GL 4"; }

    static [[nodiscard]] auto create() -> exp_ns::expected<RenderSystem, std::string>;

private:
};

} // namespace morpheus::gfx::gl4
