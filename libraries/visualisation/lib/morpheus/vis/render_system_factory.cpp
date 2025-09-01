#include <morpheus/application/po/adapters/enum.hpp>
#include <morpheus/vis/render_system_factory.hpp>

#include <boost/program_options/options_description.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace hana = boost::hana;

namespace morpheus::vis
{

//---------------------------------------------------------------------------------------------------------------------

void RenderSystemFactory::addOptions(boost::program_options::options_description& options)
{
    namespace po = boost::program_options;
    options.add_options()("render-system", po::value(&mActiveApi)->default_value(mActiveApi), "The rendering system to instantiate.");
}

// boost::program_options::options_description& RenderSystemFactory::runTuiConfiguration()
void RenderSystemFactory::runTuiConfiguration()
{
    auto const renderSystems = []()
    {
        std::vector<std::string> results;
        boost::hana::for_each(availableAPIs(),
                              [&](auto const& pair)
                              {
                                  // constexpr auto key = hana::first(pair);
                                  auto value = hana::second(pair);
                                  using RenderSystem = typename decltype(value)::type;
                                  results.push_back(std::string(RenderSystem::getGraphicsApi()));
                              });
        return results;
    }();

    using namespace ftxui;

    enum class Pages
    {
        SelectRenderSystem,
        RenderSystemSettings,
    };

    Pages current = Pages::SelectRenderSystem;
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    // -- 1. Render System selection

    int selectedRenders = 0;
    auto renderSystemRadioBox = ftxui::Radiobox(&renderSystems, &selectedRenders);
    // auto nextButton = ftxui::Button("Next", [&] { current = Pages::SelectRenderSystem; screen.PostEvent(ftxui::Event::Custom); });
    auto nextButton = ftxui::Button("Next",
                                    [&]
                                    {
                                        current = Pages::SelectRenderSystem;
                                        screen.Exit();
                                    });
    auto selectRenderSystemPage = ftxui::Container::Vertical({renderSystemRadioBox, nextButton});
    auto selectRSRenderer = Renderer(selectRenderSystemPage,
                                     [&]
                                     {
                                         return vbox({
                                                    text("Select Render System:") | bold,
                                                    renderSystemRadioBox->Render(),
                                                    separator(),
                                                    nextButton->Render(),
                                                }) |
                                                border | center;
                                     });

    // -- 2. Render System Settings selection
    screen.Loop(selectRSRenderer);

    // auto testComponent = ftxui::Renderer(selectRSRenderer,
    //     [&]()
    //     {
    //         auto rendererWin = ftxui::window(ftxui::text("Render System"), render->Render() | ftxui::vscroll_indicator | ftxui::frame);
    //         return rendererWin;
    //     });
    // screen.Loop(testComponent);
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::vis
