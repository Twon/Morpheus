#pragma once

#include <morpheus/gfx/d3d12/prerequisites.hpp>
#include <morpheus/gfx/d3d12/types.hpp>
#include <morpheus/gfx/platform/render_system.hpp>

#include <string>
#include <string_view>

namespace morpheus::gfx::d3d12
{

class Adapter;

/// \class Rrender_system
///     Rendering system abstraction based upon the Microsoft DirectX 12 API.
///
class RenderSystem : public gfx::RenderSystem
{
public:
    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApi() noexcept -> std::string_view;

    /// Get the description of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApiDescription() noexcept -> std::string_view;

    /// Creates the D3D12 render system on the specified graphics adapter.
    /// \param[in] adapter
    ///     The graphics adapter to create the device on.
    [[nodiscard]] static auto create(Adapter const& adapter) -> conf::exp::expected<RenderSystem, std::string>;

private:
    RenderSystem() = default;

    D3D12Device mDevice;
};

constexpr auto RenderSystem::getGraphicsApi() noexcept -> std::string_view
{
    return "Direct X 12";
}

constexpr auto RenderSystem::getGraphicsApiDescription() noexcept -> std::string_view
{
    return "DirectX 12: Microsoft low-level 3D graphics API optimized for Windows systems.";
}

} // namespace morpheus::gfx::d3d12
