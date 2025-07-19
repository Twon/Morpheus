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
class Visualisation {
public:

    Visualisation(Visualisation const&) = delete;
    Visualisation& operator=(Visualisation const&) = delete;

    Visualisation(Visualisation&&) = default;
    Visualisation& operator=(Visualisation&&) = default;

    exp_ns::expected<Visualisation, std::string> create(R&& renderSystem);

    /// Register program options
    void addOptions(boost::program_options::options_description& )
    {
    }

private:
    Visualisation(R&& renderSystem, typename R::Window&& window);

    R mRenderSystem;
    typename R::Window mWindow;
};

template <gfx::concepts::RenderSystem R>
Visualisation<R>::Visualisation(R&& renderSystem, typename R::Window&& window)
:   mRenderSystem(std::move(renderSystem))
,   mWindow(std::move(window))
{
}

template <gfx::concepts::RenderSystem R>
exp_ns::expected<Visualisation<R>, std::string> Visualisation<R>::create(R&& renderSystem)
{

}

} // namespace morpheus::vis
