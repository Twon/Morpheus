#include <morpheus/vis/render_system_factory.hpp>

#include <boost/program_options/options_description.hpp>

namespace morpheus::vis
{

void RenderSystemFactory::addOptions(boost::program_options::options_description& options)
{
    namespace po = boost::program_options;
    options.add_options()("render-system", po::value(&mActiveApi)->default_value(mActiveApi), "The rendering system to instantiate.");
}

//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::vis
