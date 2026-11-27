#pragma once

#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/platform/concepts/render_system.hpp>
#include <morpheus/vis/render_system_factory.hpp>
#include <morpheus/vis/tui.hpp>

#include <utility>

namespace morpheus::vis
{

/*! \class Visualisation
        The visualisation component acts as a facade encapsulating all rendering activities of an application.
    \tparam R
        The render system used by the visualisation.
 */
template <gfx::concepts::RenderSystem R>
class Visualisation
{
public:
    using RenderSystemType = R;            ///< The render system abstraction type.
    using WindowType = typename R::Window; ///< The platform window type provided by the render system.
    using Config = VisualisationConfig;    ///< The configuration options for visualisation setup.

    Visualisation(Visualisation const&) = delete;
    Visualisation& operator=(Visualisation const&) = delete;

    Visualisation(Visualisation&&) = default;
    Visualisation& operator=(Visualisation&&) = default;

    /// Create a visualisation instance from an existing render system and window.
    /// \param[in] renderSystem
    ///     The render system to own.
    /// \param[in] window
    ///     The window to own.
    /// \return An expected containing the created Visualisation or an error message.
    [[nodiscard]] static auto create(RenderSystemType&& renderSystem, WindowType&& window) -> conf::exp::expected<Visualisation, std::string>;

    /// Create a visualisation instance from an existing render system and window configuration.
    /// \param[in] renderSystem
    ///     The render system to own.
    /// \param[in] config
    ///     The configuration parameters for creating the render system's window.
    /// \return An expected containing the created Visualisation or an error message.
    [[nodiscard]] static auto create(RenderSystemType&& renderSystem, typename WindowType::Config const& config = {})
        -> conf::exp::expected<Visualisation, std::string>;

    /// Register program options for command-line parsing.
    /// \param[in,out] options
    ///     The boost options description to register with.
    auto addOptions(boost::program_options::options_description& /*options*/) -> void {}

#if (__cpp_explicit_this_parameter >= 202110L)
    /// Access the underlying render system.
    /// \return Reference to the render system matching the value category and constness of *this.
    [[nodiscard]] auto renderSystem(this auto&& self) noexcept -> decltype(auto) { return std::forward_like<decltype(self)>(self.mRenderSystem); }

    /// Access the underlying window.
    /// \return Reference to the window matching the value category and constness of *this.
    [[nodiscard]] auto window(this auto&& self) noexcept -> decltype(auto) { return std::forward_like<decltype(self)>(self.mWindow); }
#else
    /// Access the underlying render system (const).
    /// \return Const reference to the render system.
    [[nodiscard]] auto renderSystem() const noexcept -> RenderSystemType const& { return mRenderSystem; }

    /// Access the underlying render system (non-const).
    /// \return Mutable reference to the render system.
    [[nodiscard]] auto renderSystem() noexcept -> RenderSystemType& { return mRenderSystem; }

    /// Access the underlying window (const).
    /// \return Const reference to the window.
    [[nodiscard]] auto window() const noexcept -> WindowType const& { return mWindow; }

    /// Access the underlying window (non-const).
    /// \return Mutable reference to the window.
    [[nodiscard]] auto window() noexcept -> WindowType& { return mWindow; }
#endif // (__cpp_explicit_this_parameter >= 202110L)

private:
    Visualisation(RenderSystemType&& renderSystem, WindowType&& window);

    RenderSystemType mRenderSystem;
    WindowType mWindow;
};

template <gfx::concepts::RenderSystem R>
Visualisation<R>::Visualisation(RenderSystemType&& renderSystem, WindowType&& window)
    : mRenderSystem(std::move(renderSystem))
    , mWindow(std::move(window))
{}

template <gfx::concepts::RenderSystem R>
auto Visualisation<R>::create(RenderSystemType&& renderSystem, WindowType&& window) -> conf::exp::expected<Visualisation<R>, std::string>
{
    return Visualisation<R>{std::move(renderSystem), std::move(window)};
}

template <gfx::concepts::RenderSystem R>
auto Visualisation<R>::create(RenderSystemType&& renderSystem, typename WindowType::Config const& config) -> conf::exp::expected<Visualisation<R>, std::string>
{
    return Visualisation<R>{std::move(renderSystem), WindowType{config}};
}

} // namespace morpheus::vis
