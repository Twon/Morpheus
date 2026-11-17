#pragma once

#include <morpheus/gfx/platform/macos/render_window.hpp>

#include <string_view>

namespace morpheus::gfx::metal
{

/// \class RenderSystem
///     Rendering system abstraction based upon the Apple Metal graphics API.
class RenderSystem
{
public:
    using Window = macos::RenderWindow; ///< Associated platform render window type.

    /// Default constructor.
    RenderSystem() = default;

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApi() noexcept -> std::string_view;

    /// Get the description of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApiDescription() noexcept -> std::string_view;

private:
    class Implementation;
};

constexpr auto RenderSystem::getGraphicsApi() noexcept -> std::string_view
{
    return "Metal";
}

constexpr auto RenderSystem::getGraphicsApiDescription() noexcept -> std::string_view
{
    return "Apple Metal API: Low-overhead, high-performance hardware-accelerated 3D graphics for macOS.";
}

} // namespace morpheus::gfx::metal
