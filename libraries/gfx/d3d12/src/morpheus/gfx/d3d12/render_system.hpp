#pragma once

#include <morpheus/gfx/platform/render_system.hpp>
#include <morpheus/gfx/d3d12/prerequisites.hpp>
#include <morpheus/gfx/d3d12/types.hpp>

#include <string_view>
#include <string>

namespace morpheus::gfx::d3d12
{

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
    [[nodiscard]] static std::string_view getGraphicsApi() noexcept { return "Direct X 12"; }

    [[nodiscard]] static auto create() -> exp_ns::expected<RenderSystem, std::string>;

private:
    RenderSystem() = default;

    D3D12Device mDevice;
};

} // namespace morpheus::gfx::d3d12
