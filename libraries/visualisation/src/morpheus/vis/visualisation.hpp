#pragma once

#include <morpheus/gfx/platform/concepts/render_system.hpp>
#include <morpheus/vis/render_system_factory.hpp>

namespace morpheus::vis
{

/*! \class Visualisation
        The visualisation component acts as a facade encapsuating all rendering activities of an application.
    \tparam R
        The render system used by the visualisation.
 */
template <gxf::concepts::RenderSystem R>
class Visualisation {
public:

    Visualisation(Visualisation const&) = delete;
    Visualisation& operator=(Visualisation const&) = delete;

    /// Register program options
    void addOptions(boost::program_options::options_description& options)
    {
    }

private:
    R mRenderSystem;

    // N windows
};

} // namespace morpheus::vis
