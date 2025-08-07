#pragma once

#include <string_view>

namespace morpheus::gfx::metal
{

/*! \class RenderSystem
        Rendering system abstraction based upon the Metal graphics API.
 */
class RenderSystem
{
public:
    using Window = void;

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;

    RenderSystem(RenderSystem&&) = default;
    RenderSystem& operator=(RenderSystem&&) = default;

    /// Get the name of the underlying graphic API.
    [[nodiscard]] static constexpr auto getGraphicsApi() noexcept -> std::string_view { return "Metal"; }

private:
    class Implementation;
};

} // namespace morpheus::gfx::metal
