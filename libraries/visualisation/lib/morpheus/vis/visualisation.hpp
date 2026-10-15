#pragma once

#include <morpheus/core/conformance/expected.hpp>
#include <morpheus/gfx/platform/concepts/render_system.hpp>
#include <morpheus/vis/render_system_factory.hpp>

namespace morpheus::vis
{

/*! \class Visualisation
        The visualisation component acts as a facade encapsuating all rendering activities of an application.
    \tparam R
        The render system used by the visualisation.
 */
template <gfx::concepts::RenderSystem R>
class Visualisation
{
public:
    using RenderSystemType = R;
    using WindowType = typename R::Window;

    Visualisation(Visualisation const&) = delete;
    Visualisation& operator=(Visualisation const&) = delete;

    Visualisation(Visualisation&&) = default;
    Visualisation& operator=(Visualisation&&) = default;

    auto create(RenderSystemType&& renderSystem) -> conf::exp::expected<Visualisation, std::string>;

    /// Register program options
    auto addOptions(boost::program_options::options_description&) -> void {}

private:
    Visualisation(RenderSystemType&& renderSystem, WindowType&& window);

    RenderSystemType mRenderSystem;
    WindowType mWindow;

    // N windows
};

template <gfx::concepts::RenderSystem R>
Visualisation<R>::Visualisation(RenderSystemType&& renderSystem, WindowType&& window)
    : mRenderSystem(std::move(renderSystem))
    , mWindow(std::move(window))
{}

template <gfx::concepts::RenderSystem R>
auto Visualisation<R>::create(RenderSystemType&& renderSystem) -> conf::exp::expected<Visualisation<R>, std::string>
{

    return {
        Visualisation<R>{std::move(renderSystem), {}}
    };
}

} // namespace morpheus::vis
