#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/gfx/platform/os.hpp"
#include "morpheus/gfx/platform/video_mode.hpp"
#include "morpheus/vis/render_system_factory.hpp"
#include "morpheus/vis/tui.hpp"

#if (MORPHEUS_RENDER_SYSTEM_METAL)
    #include <morpheus/gfx/metal/adapter.hpp>
#endif

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <algorithm>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace morpheus::vis
{

namespace
{

/// \struct RenderSystemEntry
///     Holds descriptor metadata for an available graphics API backend.
struct RenderSystemEntry
{
    API api;
    std::string name;
    std::string description;
};

/// \struct HardwareAdapterEntry
///     Describes a queried graphics hardware device and its supported video modes.
struct HardwareAdapterEntry
{
    std::string name;
    std::string details;
    std::vector<gfx::VideoMode> videoModes;
    std::vector<std::string> videoModeLabels;
};

/// \brief Parse a string to an unsigned 16-bit integer with fallback.
/// \param[in] str
///     Input string to parse.
/// \param[in] fallback
///     Default value returned if parsing fails.
/// \return Parsed value or fallback.
auto parseUInt16(std::string const& str, std::uint16_t const fallback) -> std::uint16_t
{
    try
    {
        unsigned long const val = std::stoul(str);
        if (val > 0 && val <= 65535)
        {
            return static_cast<std::uint16_t>(val);
        }
    }
    catch (...)
    {}
    return fallback;
}

/// \brief Query all available graphics backends from the RenderSystemFactory.
/// \return List of supported render system entries.
auto getAvailableSystems() -> std::vector<RenderSystemEntry>
{
    std::vector<RenderSystemEntry> systems;
    boost::hana::for_each(RenderSystemFactory::availableAPIs(),
                          [&](auto const& pair)
                          {
                              auto key = boost::hana::first(pair);
                              auto value = boost::hana::second(pair);
                              using KeyType = typename decltype(key)::type;
                              using RenderSystem = typename decltype(value)::type;
                              API const api = KeyType::value;
                              std::string name = std::string(RenderSystem::getGraphicsApi());
                              std::string desc = std::string(RenderSystem::getGraphicsApiDescription());
                              systems.push_back({api, std::move(name), std::move(desc)});
                          });
    return systems;
}

/// \brief Query available render systems and resolve initial selection.
/// \param[in] initialApi
///     The initial API backend to select.
/// \return Tuple of (available systems, display names, initially selected index).
auto getRenderSystemsInfo(API const initialApi) -> std::tuple<std::vector<RenderSystemEntry>, std::vector<std::string>, int>
{
    auto availableSystems = getAvailableSystems();
    auto renderSystemNames =
        availableSystems | conf::ranges::views::transform([](auto const& e) { return e.name; }) | conf::ranges::to<std::vector<std::string>>();
    auto const selectedRenderSystemIt = conf::ranges::find_if(availableSystems, [&](auto const& e) { return e.api == initialApi; });
    auto const selectedRenderSystem =
        selectedRenderSystemIt != availableSystems.end() ? static_cast<int>(conf::ranges::distance(availableSystems.begin(), selectedRenderSystemIt)) : 0;
    return std::tuple(std::move(availableSystems), std::move(renderSystemNames), selectedRenderSystem);
}

/// \brief Query hardware display modes from system monitors as a fallback or cross-platform query.
/// \return List of video modes detected on connected displays.
auto queryFallbackVideoModes() -> std::vector<gfx::VideoMode>
{
    std::vector<gfx::VideoMode> modes;
    for (auto const& monitor : gfx::os::enumerateMonitors())
    {
        gfx::VideoMode const vm{static_cast<std::uint16_t>(monitor.width()), static_cast<std::uint16_t>(monitor.height()), 32, 60};
        if (std::find(modes.begin(), modes.end(), vm) == modes.end())
        {
            modes.push_back(vm);
        }
    }
    if (modes.empty())
    {
        modes.emplace_back(1920, 1080, 32, 60);
        modes.emplace_back(1280, 720, 32, 60);
        modes.emplace_back(800, 600, 32, 60);
    }
    return modes;
}

/// \brief Query real hardware adapters and video modes for the selected graphics API.
/// \param[in] api
///     The selected graphics backend API.
/// \return List of hardware adapters with their respective video modes.
auto queryAdaptersForApi(API const api) -> std::vector<HardwareAdapterEntry>
{
    std::vector<HardwareAdapterEntry> result;

#if (MORPHEUS_RENDER_SYSTEM_METAL)
    if (api == API::Metal)
    {
        auto metalAdapters = gfx::metal::enumerateAdapters();
        for (auto const& adapter : metalAdapters)
        {
            HardwareAdapterEntry entry;
            entry.name = std::string(adapter.name());

            std::string details = conf::fmt::format("Registry ID: {:#x}", adapter.id());
            if (adapter.isLowPower())
            {
                details += " | Low-Power GPU";
            }
            if (adapter.isRemovable())
            {
                details += " | External eGPU";
            }
            if (adapter.memory() > 0)
            {
                double const memGb = static_cast<double>(adapter.memory()) / (1024.0 * 1024.0 * 1024.0);
                details += conf::fmt::format(" | Max Working Memory: {:.1f} GB", memGb);
            }
            entry.details = std::move(details);
            entry.videoModes = adapter.getVideoModes();

            for (auto const& vm : entry.videoModes)
            {
                entry.videoModeLabels.push_back(conf::fmt::format("{} x {} @ {} Hz ({} bpp)", vm.width(), vm.height(), vm.refreshRate(), vm.colourDepth()));
            }
            result.push_back(std::move(entry));
        }
    }
#endif

    if (result.empty())
    {
        HardwareAdapterEntry fallbackEntry;
        std::string const apiName =
            (api == API::Vulkan ? "Vulkan Physical Device" : (api == API::OpenGL4 ? "OpenGL Graphics Device" : "Default Graphics Adapter"));
        fallbackEntry.name = apiName;
        fallbackEntry.details = "Hardware device queried through system display configuration.";
        fallbackEntry.videoModes = queryFallbackVideoModes();
        for (auto const& vm : fallbackEntry.videoModes)
        {
            fallbackEntry.videoModeLabels.push_back(conf::fmt::format("{} x {} @ {} Hz ({} bpp)", vm.width(), vm.height(), vm.refreshRate(), vm.colourDepth()));
        }
        result.push_back(std::move(fallbackEntry));
    }

    return result;
}

/// \struct TuiContext
///     Shared state across the individual TUI tabs.
struct TuiContext
{
    // Render system state
    std::vector<RenderSystemEntry> availableSystems;
    std::vector<std::string> renderSystemNames;
    int selectedRenderSystem = 0;

    // Hardware adapters & video modes
    std::vector<HardwareAdapterEntry> adapters;
    std::vector<std::string> adapterNames;
    int selectedAdapter = 0;
    std::vector<std::string> videoModeLabels;
    int selectedVideoMode = 0;

    // Window options
    std::string windowTitle;
    std::string widthStr;
    std::string heightStr;
    std::string startXStr;
    std::string startYStr;
    std::vector<std::string> colourDepthOptions = {"32-bit (RGBA8888)", "24-bit (RGB888)", "16-bit (RGB565)"};
    int selectedColourDepth = 0;
    bool isFullscreen = false;
    bool isVisible = true;

    // Render system specific options
    bool enableValidation = false;
    bool enableDebugOutput = false;
    bool preferIntegratedGpu = false;
    bool enableTearing = false;
    bool enableDxil = false;
    bool coreProfile = true;
    bool vsync = true;

    // Visualisation options
    std::vector<std::string> msaaOptions = {"1x (Disabled)", "2x MSAA", "4x MSAA (Recommended)", "8x MSAA (High Quality)"};
    std::vector<int> msaaValues = {1, 2, 4, 8};
    int selectedMsaa = 0;

    std::vector<std::string> fpsOptions = {
        "30 FPS (Power Saver)", "60 FPS (Standard)", "120 FPS (High Refresh)", "144 FPS (Competitive)", "Unlimited (Uncapped)"};
    std::vector<int> fpsValues = {30, 60, 120, 144, 0};
    int selectedFps = 1;

    std::vector<std::string> themeOptions = {"Dark Slate (#1E222B)", "Midnight Black (#000000)", "Cornflower Blue (#6495ED)", "Graphite Gray (#2E3440)"};
    int selectedTheme = 0;

    // Screen navigation
    std::vector<std::string> tabTitles = {
        " 1. Render System ",
        " 2. Adapters & Modes ",
        " 3. Render Settings ",
        " 4. Visualisation ",
        " 5. Summary & Launch ",
    };
    int activeTab = 0;
    bool confirmed = false;

    /// Refresh adapters and video modes for the currently selected render system.
    void refreshAdaptersAndModes()
    {
        if (selectedRenderSystem >= 0 && selectedRenderSystem < static_cast<int>(availableSystems.size()))
        {
            adapters = queryAdaptersForApi(availableSystems[selectedRenderSystem].api);
        }
        else
        {
            adapters = queryAdaptersForApi(API::Metal);
        }

        adapterNames.clear();
        for (auto const& a : adapters)
        {
            adapterNames.push_back(a.name);
        }
        selectedAdapter = 0;
        updateVideoModesForSelectedAdapter();
    }

    /// Update video mode list for the currently selected adapter.
    void updateVideoModesForSelectedAdapter()
    {
        videoModeLabels.clear();
        if (selectedAdapter >= 0 && selectedAdapter < static_cast<int>(adapters.size()))
        {
            videoModeLabels = adapters[selectedAdapter].videoModeLabels;
        }
        if (videoModeLabels.empty())
        {
            videoModeLabels.push_back("1920 x 1080 @ 60 Hz (32 bpp)");
        }
        selectedVideoMode = 0;
        applySelectedVideoMode();
    }

    /// Apply the currently selected video mode dimensions to the window settings.
    void applySelectedVideoMode()
    {
        if (selectedAdapter >= 0 && selectedAdapter < static_cast<int>(adapters.size()))
        {
            auto const& modes = adapters[selectedAdapter].videoModes;
            if (selectedVideoMode >= 0 && selectedVideoMode < static_cast<int>(modes.size()))
            {
                auto const& vm = modes[selectedVideoMode];
                widthStr = std::to_string(vm.width());
                heightStr = std::to_string(vm.height());

                if (vm.colourDepth() == 16)
                {
                    selectedColourDepth = 2;
                }
                else if (vm.colourDepth() == 24)
                {
                    selectedColourDepth = 1;
                }
                else
                {
                    selectedColourDepth = 0;
                }

                for (std::size_t i = 0; i < fpsValues.size(); ++i)
                {
                    if (fpsValues[i] == vm.refreshRate())
                    {
                        selectedFps = static_cast<int>(i);
                        break;
                    }
                }
            }
        }
    }
};

/// \brief Create the header banner component.
/// \return FTXUI element representing the header.
auto createHeader() -> ftxui::Element
{
    using namespace ftxui;
    return vbox({
        hbox({
            text(" MORPHEUS ") | bold | inverted | color(Color::Cyan),
            text(" Visualisation & Window Configuration ") | bold | color(Color::White),
            filler(),
            text("[FTXUI] ") | dim,
        }),
        separator(),
    });
}

/// \brief Create the footer component with keyboard shortcuts.
/// \return FTXUI element representing the footer.
auto createFooter() -> ftxui::Element
{
    using namespace ftxui;
    return vbox({
        separator(),
        hbox({
            text("Keys: ") | dim,
            text("Tab / Shift-Tab") | bold | color(Color::Cyan),
            text(" Navigate Controls  |  ") | dim,
            text("Space / Enter") | bold | color(Color::Cyan),
            text(" Toggle/Select  |  ") | dim,
            text("Esc") | bold | color(Color::RedLight),
            text(" Cancel") | dim,
        }) | center,
    });
}

/// \brief Tab 1: Render System Selection.
/// \param[in,out] context
///     Shared TUI state context.
/// \param[in] onSystemChanged
///     Callback triggered when the render system selection changes.
/// \return FTXUI component for Tab 1.
auto createRenderSystemTab(TuiContext& context, std::function<void()> onSystemChanged) -> ftxui::Component
{
    using namespace ftxui;

    auto radiobox = Radiobox(&context.renderSystemNames, &context.selectedRenderSystem);
    int lastSelected = context.selectedRenderSystem;

    auto container = Container::Vertical({radiobox});

    return Renderer(container,
                    [=, &context]() mutable
                    {
                        if (context.selectedRenderSystem != lastSelected)
                        {
                            lastSelected = context.selectedRenderSystem;
                            if (onSystemChanged)
                            {
                                onSystemChanged();
                            }
                        }

                        return vbox({
                            text("1. Select Target Graphics Render System") | bold | color(Color::Cyan),
                            text("Choose the underlying graphics API hardware backend:") | dim,
                            separator(),
                            hbox({
                                vbox({
                                    text("Available Backends:") | bold,
                                    radiobox->Render(),
                                }) | flex,
                                separator(),
                                vbox({
                                    text("API Details:") | bold,
                                    text(context.availableSystems[context.selectedRenderSystem].name) | bold | color(Color::Yellow),
                                    separator(),
                                    paragraph(context.availableSystems[context.selectedRenderSystem].description),
                                    separator(),
                                    text("Query status: Hardware adapters will be queried on next tab.") | color(Color::GreenLight),
                                }) | flex,
                            }),
                        });
                    });
}

/// \brief Tab 2: Hardware Adapters and Video Modes Query.
/// \param[in,out] context
///     Shared TUI state context.
/// \param[in] onAdapterChanged
///     Callback invoked when a different adapter is chosen.
/// \param[in] onModeChanged
///     Callback invoked when a different video mode is chosen.
/// \return FTXUI component for Tab 2.
auto createAdapterVideoModeTab(TuiContext& context, std::function<void()> onAdapterChanged, std::function<void()> onModeChanged) -> ftxui::Component
{
    using namespace ftxui;

    auto adapterRadiobox = Radiobox(&context.adapterNames, &context.selectedAdapter);
    auto modeRadiobox = Radiobox(&context.videoModeLabels, &context.selectedVideoMode);

    auto applyBtn = Button("Apply Video Mode to Window Settings",
                           [&context, onModeChanged]
                           {
                               context.applySelectedVideoMode();
                               if (onModeChanged)
                               {
                                   onModeChanged();
                               }
                           });

    int lastAdapter = context.selectedAdapter;
    int lastMode = context.selectedVideoMode;

    auto container = Container::Vertical({
        adapterRadiobox,
        modeRadiobox,
        applyBtn,
    });

    return Renderer(container,
                    [=, &context]() mutable
                    {
                        if (context.selectedAdapter != lastAdapter)
                        {
                            lastAdapter = context.selectedAdapter;
                            if (onAdapterChanged)
                            {
                                onAdapterChanged();
                            }
                        }

                        if (context.selectedVideoMode != lastMode)
                        {
                            lastMode = context.selectedVideoMode;
                            context.applySelectedVideoMode();
                            if (onModeChanged)
                            {
                                onModeChanged();
                            }
                        }

                        std::string adapterDetails;
                        if (context.selectedAdapter >= 0 && context.selectedAdapter < static_cast<int>(context.adapters.size()))
                        {
                            adapterDetails = context.adapters[context.selectedAdapter].details;
                        }

                        return vbox({
                            text("2. Hardware Adapters & Display Video Modes") | bold | color(Color::Cyan),
                            text("Queried real devices and supported display modes for: " + context.availableSystems[context.selectedRenderSystem].name) | dim,
                            separator(),
                            hbox({
                                // Left: Adapters
                                vbox({
                                    text("Detected Adapters (GPUs):") | bold,
                                    adapterRadiobox->Render(),
                                    separator(),
                                    text("Device Information:") | bold,
                                    paragraph(adapterDetails) | color(Color::GreenLight),
                                }) | flex,
                                separator(),
                                // Right: Video Modes
                                vbox({
                                    text("Available Video Modes (Resolution & Refresh Rate):") | bold,
                                    modeRadiobox->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 12),
                                    separator(),
                                    applyBtn->Render() | center,
                                }) | flex,
                            }),
                        });
                    });
}

/// \brief Tab 3: Render System Specific Settings.
/// \param[in,out] context
///     Shared TUI state context.
/// \return FTXUI component for Tab 3.
auto createRenderSettingsTab(TuiContext& context) -> ftxui::Component
{
    using namespace ftxui;

    auto cbValidation = Checkbox("Enable Validation Layers / Debug Runtime", &context.enableValidation);
    auto cbDebug = Checkbox("Enable Debug Output Messages", &context.enableDebugOutput);
    auto cbLowPower = Checkbox("Prefer Low-Power / Integrated GPU", &context.preferIntegratedGpu);
    auto cbTearing = Checkbox("Enable Tearing / Variable Refresh Rate", &context.enableTearing);
    auto cbDxil = Checkbox("Enable Modern DXIL Shader Compiler", &context.enableDxil);
    auto cbCore = Checkbox("OpenGL Core Profile (vs Compatibility)", &context.coreProfile);
    auto cbVsync = Checkbox("Enable Vertical Sync (V-Sync)", &context.vsync);

    auto container = Container::Vertical({
        cbValidation,
        cbDebug,
        cbLowPower,
        cbTearing,
        cbDxil,
        cbCore,
        cbVsync,
    });

    return Renderer(
        container,
        [=, &context]
        {
            API const currentApi = context.availableSystems[context.selectedRenderSystem].api;
            Elements apiOptions;

            if (currentApi == API::Metal)
            {
                apiOptions.push_back(cbValidation->Render());
                apiOptions.push_back(cbLowPower->Render());
                apiOptions.push_back(cbVsync->Render());
                apiOptions.push_back(text("Note: Metal validation enables GPU runtime diagnostics in macOS.") | dim);
            }
            else if (currentApi == API::Vulkan)
            {
                apiOptions.push_back(cbValidation->Render());
                apiOptions.push_back(cbLowPower->Render());
                apiOptions.push_back(cbVsync->Render());
                apiOptions.push_back(text("Note: Requires VK_LAYER_KHRONOS_validation installed on system.") | dim);
            }
            else if (currentApi == API::OpenGL4)
            {
                apiOptions.push_back(cbCore->Render());
                apiOptions.push_back(cbDebug->Render());
                apiOptions.push_back(cbVsync->Render());
            }
            else if (currentApi == API::D3D12)
            {
                apiOptions.push_back(cbValidation->Render());
                apiOptions.push_back(cbDxil->Render());
                apiOptions.push_back(cbTearing->Render());
                apiOptions.push_back(cbVsync->Render());
            }

            return vbox({
                text("3. Render System Specific Settings (" + context.availableSystems[context.selectedRenderSystem].name + ")") | bold | color(Color::Cyan),
                text(context.availableSystems[context.selectedRenderSystem].description) | dim,
                separator(),
                vbox(std::move(apiOptions)),
            });
        });
}

/// \brief Tab 4: Visualisation Settings.
/// \param[in,out] context
///     Shared TUI state context.
/// \return FTXUI component for Tab 4.
auto createVisualisationTab(TuiContext& context) -> ftxui::Component
{
    using namespace ftxui;

    auto msaaRadiobox = Radiobox(&context.msaaOptions, &context.selectedMsaa);
    auto fpsRadiobox = Radiobox(&context.fpsOptions, &context.selectedFps);
    auto themeRadiobox = Radiobox(&context.themeOptions, &context.selectedTheme);

    auto container = Container::Vertical({
        msaaRadiobox,
        fpsRadiobox,
        themeRadiobox,
    });

    return Renderer(container,
                    [=]
                    {
                        return vbox({
                            text("4. Visualisation Parameters") | bold | color(Color::Cyan),
                            separator(),
                            hbox({
                                vbox({
                                    text("Multisample Anti-Aliasing (MSAA):") | bold | color(Color::Cyan),
                                    separator(),
                                    msaaRadiobox->Render(),
                                }) | flex,
                                separator(),
                                vbox({
                                    text("Target Refresh Rate:") | bold | color(Color::Cyan),
                                    separator(),
                                    fpsRadiobox->Render(),
                                }) | flex,
                                separator(),
                                vbox({
                                    text("Clear Color & Theme:") | bold | color(Color::Cyan),
                                    separator(),
                                    themeRadiobox->Render(),
                                }) | flex,
                            }),
                        });
                    });
}

/// \brief Tab 5: Window Configuration and Launch Summary.
/// \param[in,out] context
///     Shared TUI state context.
/// \param[in] onLaunch
///     Callback triggered to launch the window.
/// \param[in] onReturn
///     Callback triggered to return to earlier settings.
/// \param[in] onExit
///     Callback triggered to cancel/exit.
/// \return FTXUI component for Tab 5.
auto createWindowSummaryTab(TuiContext& context, std::function<void()> onLaunch, std::function<void()> onReturn, std::function<void()> onExit)
    -> ftxui::Component
{
    using namespace ftxui;

    auto inputTitle = Input(&context.windowTitle, "Window Title");
    auto inputWidth = Input(&context.widthStr, "Width");
    auto inputHeight = Input(&context.heightStr, "Height");
    auto inputPosX = Input(&context.startXStr, "Start X");
    auto inputPosY = Input(&context.startYStr, "Start Y");
    auto cbFullscreen = Checkbox("Start in Full Screen Mode", &context.isFullscreen);
    auto cbVisible = Checkbox("Initially Visible", &context.isVisible);
    auto depthRadiobox = Radiobox(&context.colourDepthOptions, &context.selectedColourDepth);

    auto launchBtn = Button(" Launch Window ", onLaunch, ButtonOption::Animated(Color::Green));
    auto returnBtn = Button(" Return to Settings ", onReturn);
    auto exitBtn = Button(" Exit without Launching ", onExit);

    auto container = Container::Vertical({
        inputTitle,
        inputWidth,
        inputHeight,
        inputPosX,
        inputPosY,
        depthRadiobox,
        cbFullscreen,
        cbVisible,
        Container::Horizontal({launchBtn, returnBtn, exitBtn}),
    });

    return Renderer(container,
                    [=, &context]
                    {
                        std::string const adapterName =
                            (!context.adapterNames.empty() && context.selectedAdapter < static_cast<int>(context.adapterNames.size()))
                                ? context.adapterNames[context.selectedAdapter]
                                : "Default GPU";

                        std::string const modeStr =
                            (!context.videoModeLabels.empty() && context.selectedVideoMode < static_cast<int>(context.videoModeLabels.size()))
                                ? context.videoModeLabels[context.selectedVideoMode]
                                : (context.widthStr + " x " + context.heightStr);

                        return vbox({
                            text("5. Window Setup & Configuration Summary") | bold | color(Color::Cyan),
                            separator(),
                            hbox({
                                // Left: Window Parameters
                                vbox({
                                    text("Window Configuration:") | bold | color(Color::GreenLight),
                                    separator(),
                                    hbox(text("Title:   ") | bold, inputTitle->Render() | border | size(WIDTH, GREATER_THAN, 24)),
                                    hbox({
                                        text("Width:   ") | bold,
                                        inputWidth->Render() | border | size(WIDTH, EQUAL, 8),
                                        text(" Height: ") | bold,
                                        inputHeight->Render() | border | size(WIDTH, EQUAL, 8),
                                    }),
                                    hbox({
                                        text("Start X: ") | bold,
                                        inputPosX->Render() | border | size(WIDTH, EQUAL, 8),
                                        text(" Start Y: ") | bold,
                                        inputPosY->Render() | border | size(WIDTH, EQUAL, 8),
                                    }),
                                    text("Colour Depth:") | bold,
                                    depthRadiobox->Render(),
                                    cbFullscreen->Render(),
                                    cbVisible->Render(),
                                }) | flex,
                                separator(),
                                // Right: Summary Overview
                                vbox({
                                    text("Hardware & Backend Review:") | bold | color(Color::Yellow),
                                    separator(),
                                    text("  • Render API:   " + context.availableSystems[context.selectedRenderSystem].name) | bold,
                                    text("  • GPU Adapter:  " + adapterName),
                                    text("  • Video Mode:   " + modeStr),
                                    text("  • Anti-Alias:   " + context.msaaOptions[context.selectedMsaa]),
                                    text("  • Target FPS:   " + context.fpsOptions[context.selectedFps]),
                                    text("  • View Theme:   " + context.themeOptions[context.selectedTheme]),
                                    text(std::string("  • V-Sync:       ") + (context.vsync ? "Enabled" : "Disabled")),
                                    text(std::string("  • Validation:   ") + (context.enableValidation ? "Enabled" : "Disabled")),
                                }) | border |
                                    flex,
                            }),
                            separator(),
                            hbox({
                                launchBtn->Render() | color(Color::GreenLight) | bold,
                                text("  "),
                                returnBtn->Render(),
                                text("  "),
                                exitBtn->Render() | color(Color::RedLight),
                            }) | center,
                        });
                    });
}

/// \brief Create the global navigation bar across all tabs.
/// \param[in,out] context
///     Shared TUI state context.
/// \param[in] numTabs
///     Total number of tabs.
/// \param[in] onLaunch
///     Launch callback.
/// \param[in] onCancel
///     Cancel callback.
/// \return FTXUI component for the navigation bar.
auto createNavigationBar(TuiContext& context, int const numTabs, std::function<void()> onLaunch, std::function<void()> onCancel) -> ftxui::Component
{
    using namespace ftxui;

    auto prevBtn = Button(" < Previous ", [&context] { context.activeTab = std::max(0, context.activeTab - 1); });
    auto nextBtn = Button(" Next > ", [&context, numTabs] { context.activeTab = std::min(numTabs - 1, context.activeTab + 1); });
    auto launchBtn = Button(" Launch Window ", onLaunch);
    auto exitBtn = Button(" Cancel / Exit ", onCancel);

    return Container::Horizontal({
        prevBtn,
        nextBtn,
        launchBtn,
        exitBtn,
    });
}

} // namespace

auto Tui::run(VisualisationConfig const& initial) -> std::optional<VisualisationConfig>
{
    using namespace ftxui;

    TuiContext context;
    auto [availableSystems, renderSystemNames, selectedRenderSystem] = getRenderSystemsInfo(initial.selectedApi);
    context.availableSystems = std::move(availableSystems);
    context.renderSystemNames = std::move(renderSystemNames);
    context.selectedRenderSystem = selectedRenderSystem;

    // Query hardware adapters and video modes for the active API
    context.refreshAdaptersAndModes();

    // Initial window state
    context.windowTitle = initial.windowConfig.windowName;
    context.widthStr = std::to_string(initial.windowConfig.width);
    context.heightStr = std::to_string(initial.windowConfig.height);
    context.startXStr = std::to_string(initial.windowConfig.startX);
    context.startYStr = std::to_string(initial.windowConfig.startY);
    context.selectedColourDepth = (initial.windowConfig.colourDepth == 16 ? 2 : (initial.windowConfig.colourDepth == 24 ? 1 : 0));
    context.isFullscreen = initial.windowConfig.fullScreen;
    context.isVisible = initial.windowConfig.visible;

    // Initial render and vis flags
    context.enableValidation = initial.enableValidationLayers;
    context.enableDebugOutput = initial.enableDebugOutput;
    context.preferIntegratedGpu = initial.preferIntegratedGpu;
    context.enableTearing = initial.enableTearing;
    context.enableDxil = initial.enableDxil;
    context.coreProfile = initial.coreProfile;
    context.vsync = initial.vsync;

    auto screen = ScreenInteractive::TerminalOutput();

    auto onLaunch = [&context, &screen]
    {
        context.confirmed = true;
        screen.Exit();
    };

    auto onCancel = [&context, &screen]
    {
        context.confirmed = false;
        screen.Exit();
    };

    auto onReturn = [&context] { context.activeTab = 0; };

    // Build tabs using single responsibility principle
    auto tab0 = createRenderSystemTab(context, [&context] { context.refreshAdaptersAndModes(); });
    auto tab1 = createAdapterVideoModeTab(context, [&context] { context.updateVideoModesForSelectedAdapter(); }, [] {});
    auto tab2 = createRenderSettingsTab(context);
    auto tab3 = createVisualisationTab(context);
    auto tab4 = createWindowSummaryTab(context, onLaunch, onReturn, onCancel);

    auto tabContent = Container::Tab({tab0, tab1, tab2, tab3, tab4}, &context.activeTab);
    auto tabMenu = Menu(&context.tabTitles, &context.activeTab, MenuOption::HorizontalAnimated());
    auto navBar = createNavigationBar(context, static_cast<int>(context.tabTitles.size()), onLaunch, onCancel);

    auto mainLayout = Container::Vertical({
        tabMenu,
        tabContent,
        navBar,
    });

    auto rootRenderer = Renderer(mainLayout,
                                 [&]
                                 {
                                     return vbox({
                                                createHeader(),
                                                tabMenu->Render() | center,
                                                separator(),
                                                tabContent->Render() | flex,
                                                separator(),
                                                navBar->Render(),
                                                createFooter(),
                                            }) |
                                            border;
                                 });

    auto rootWithEvents = CatchEvent(rootRenderer,
                                     [&](Event event)
                                     {
                                         if (event == Event::Escape)
                                         {
                                             context.confirmed = false;
                                             screen.Exit();
                                             return true;
                                         }
                                         return false;
                                     });

    screen.Loop(rootWithEvents);

    if (!context.confirmed)
    {
        return std::nullopt;
    }

    VisualisationConfig result = initial;
    result.selectedApi = context.availableSystems[context.selectedRenderSystem].api;
    result.renderSystemName = context.availableSystems[context.selectedRenderSystem].name;

    result.windowConfig.windowName = context.windowTitle;
    result.windowConfig.width = parseUInt16(context.widthStr, initial.windowConfig.width);
    result.windowConfig.height = parseUInt16(context.heightStr, initial.windowConfig.height);
    result.windowConfig.startX = parseUInt16(context.startXStr, initial.windowConfig.startX);
    result.windowConfig.startY = parseUInt16(context.startYStr, initial.windowConfig.startY);
    result.windowConfig.colourDepth = (context.selectedColourDepth == 2 ? 16 : (context.selectedColourDepth == 1 ? 24 : 32));
    result.windowConfig.fullScreen = context.isFullscreen;
    result.windowConfig.visible = context.isVisible;

    result.enableValidationLayers = context.enableValidation;
    result.enableDebugOutput = context.enableDebugOutput;
    result.preferIntegratedGpu = context.preferIntegratedGpu;
    result.enableTearing = context.enableTearing;
    result.enableDxil = context.enableDxil;
    result.coreProfile = context.coreProfile;
    result.vsync = context.vsync;

    result.msaaSamples = context.msaaValues[context.selectedMsaa];
    result.targetFps = context.fpsValues[context.selectedFps];
    result.theme = context.themeOptions[context.selectedTheme];

    return result;
}

} // namespace morpheus::vis
