#pragma once

#include <morpheus/core/conformance/expected.hpp>
// #include <morpheus/gfx/gl4/prerequisites.hpp>
#include <morpheus/gfx/platform/render_system.hpp>

#include <string>
#include <string_view>

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
    using RenderWindow = typename T::RenderWindow;
    using Window = RenderWindow;

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApi() noexcept -> std::string_view { return "Open GL 4"; }

    /// Get the description of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApiDescription() noexcept -> std::string_view;

    [[nodiscard]] static auto create() -> conf::exp::expected<RenderSystem, std::string>;

private:
};

template <class T>
constexpr auto RenderSystem<T>::getGraphicsApiDescription() noexcept -> std::string_view
{
    return "OpenGL 4.x Core: Proven cross-platform graphics standard with wide hardware support.";
}

} // namespace morpheus::gfx::gl4
