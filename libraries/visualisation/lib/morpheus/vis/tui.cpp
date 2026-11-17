#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/vis/render_system_factory.hpp"
#include "morpheus/vis/tui.hpp"

#include <morpheus/gfx/platform/os.hpp>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace morpheus::vis
{

namespace
{

struct RenderSystemEntry
{
    API api;
    std::string name;
    std::string description;
};

struct ResPreset
{
    std::string label;
    std::uint16_t width;
    std::uint16_t height;
};

auto parseUInt16(std::string const& str, std::uint16_t fallback) -> std::uint16_t
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

auto getAvailableSystems() -> std::vector<RenderSystemEntry>
{
    std::vector<RenderSystemEntry> available_systems;
    boost::hana::for_each(RenderSystemFactory::availableAPIs(),
                          [&](auto const& pair)
                          {
                              auto key = boost::hana::first(pair);
                              auto value = boost::hana::second(pair);
                              using KeyType = typename decltype(key)::type;
                              using RenderSystem = typename decltype(value)::type;
                              API api = KeyType::value;
                              std::string name = std::string(RenderSystem::getGraphicsApi());
                              std::string desc = std::string(RenderSystem::getGraphicsApiDescription());
                              available_systems.push_back({api, std::move(name), std::move(desc)});
                          });
    return available_systems;
}

} // namespace

auto Tui::run(VisualisationConfig const& initial) -> std::optional<VisualisationConfig>
{
    using namespace ftxui;

    auto const availableSystems = getAvailableSystems();
    auto const renderSystemNames =
        availableSystems | conf::ranges::views::transform([](auto const& e) { return e.name; }) | conf::ranges::to<std::vector<std::string>>();
    auto const selectedRenderSystemIt = conf::ranges::find_if(availableSystems, [&](auto const& e) { return e.api == initial.selectedApi; });
    auto selectedRenderSystem =
        selectedRenderSystemIt != availableSystems.end() ? static_cast<int>(conf::ranges::distance(availableSystems.begin(), selectedRenderSystemIt)) : 0;

    // Detected Monitors
    std::vector<std::string> detected_monitors;
    std::uint16_t primary_monitor_width = 1920;
    std::uint16_t primary_monitor_height = 1080;
    bool found_primary = false;
    for (auto const& monitor : gfx::os::enumerateMonitors())
    {
        detected_monitors.push_back(conf::fmt::format("{}", monitor));
        if (monitor.primary() || !found_primary)
        {
            primary_monitor_width = static_cast<std::uint16_t>(monitor.width());
            primary_monitor_height = static_cast<std::uint16_t>(monitor.height());
            if (monitor.primary())
            {
                found_primary = true;
            }
        }
    }

    // Window options state
    std::string window_title = initial.windowConfig.windowName;
    std::string width_str = std::to_string(initial.windowConfig.width);
    std::string height_str = std::to_string(initial.windowConfig.height);
    std::string start_x_str = std::to_string(initial.windowConfig.startX);
    std::string start_y_str = std::to_string(initial.windowConfig.startY);

    std::vector<ResPreset> const presets = {
        {       "800 x 600 (SVGA)",  800,  600},
        {       "1024 x 768 (XGA)", 1024,  768},
        {   "1280 x 720 (720p HD)", 1280,  720},
        {"1920 x 1080 (1080p FHD)", 1920, 1080},
        {"2560 x 1440 (1440p QHD)", 2560, 1440},
        {   "3840 x 2160 (4K UHD)", 3840, 2160},
        {                 "Custom",    0,    0},
    };
    std::vector<std::string> preset_labels;
    for (auto const& p : presets)
    {
        preset_labels.push_back(p.label);
    }
    int selected_preset = static_cast<int>(presets.size()) - 1; // Default to Custom
    for (std::size_t i = 0; i < presets.size() - 1; ++i)
    {
        if (presets[i].width == initial.windowConfig.width && presets[i].height == initial.windowConfig.height)
        {
            selected_preset = static_cast<int>(i);
            break;
        }
    }

    std::vector<std::string> colour_depth_options = {
        "32-bit (RGBA8888)",
        "24-bit (RGB888)",
        "16-bit (RGB565)",
    };
    int selected_colour_depth = 0;
    if (initial.windowConfig.colourDepth == 16)
    {
        selected_colour_depth = 2;
    }
    else if (initial.windowConfig.colourDepth == 24)
    {
        selected_colour_depth = 1;
    }

    bool is_fullscreen = initial.windowConfig.fullScreen;
    bool is_visible = initial.windowConfig.visible;

    // Render System settings state
    bool enable_validation = initial.enableValidationLayers;
    bool enable_debug_output = initial.enableDebugOutput;
    bool prefer_integrated_gpu = initial.preferIntegratedGpu;
    bool enable_tearing = initial.enableTearing;
    bool enable_dxil = initial.enableDxil;
    bool core_profile = initial.coreProfile;
    bool vsync = initial.vsync;

    // Visualisation settings state
    std::vector<std::string> msaa_options = {"1x (Disabled)", "2x MSAA", "4x MSAA (Recommended)", "8x MSAA (High Quality)"};
    std::vector<int> const msaa_values = {1, 2, 4, 8};
    int selected_msaa = 0;
    for (std::size_t i = 0; i < msaa_values.size(); ++i)
    {
        if (msaa_values[i] == initial.msaaSamples)
        {
            selected_msaa = static_cast<int>(i);
            break;
        }
    }

    std::vector<std::string> fps_options = {
        "30 FPS (Power Saver)", "60 FPS (Standard)", "120 FPS (High Refresh)", "144 FPS (Competitive)", "Unlimited (Uncapped)"};
    std::vector<int> const fps_values = {30, 60, 120, 144, 0};
    int selected_fps = 1; // Default to 60 FPS
    for (std::size_t i = 0; i < fps_values.size(); ++i)
    {
        if (fps_values[i] == initial.targetFps)
        {
            selected_fps = static_cast<int>(i);
            break;
        }
    }

    std::vector<std::string> theme_options = {"Dark Slate (#1E222B)", "Midnight Black (#000000)", "Cornflower Blue (#6495ED)", "Graphite Gray (#2E3440)"};
    int selected_theme = 0;
    for (std::size_t i = 0; i < theme_options.size(); ++i)
    {
        if (theme_options[i].find(initial.theme) != std::string::npos)
        {
            selected_theme = static_cast<int>(i);
            break;
        }
    }

    // Navigation and screen state
    int activeTab = 0;
    std::vector<std::string> tabTitles = {
        " 1. Render System ",
        " 2. Window Setup ",
        " 3. Render Settings ",
        " 4. Visualisation ",
        " 5. Summary & Launch ",
    };
    bool confirmed = false;

    auto screen = ScreenInteractive::TerminalOutput();

    // -- Tab 0: Render System Components
    auto render_system_radiobox = Radiobox(&renderSystemNames, &selectedRenderSystem);
    auto tab0_container = Container::Vertical({render_system_radiobox});

    // -- Tab 1: Window Setup Components
    auto input_title = Input(&window_title, "Window Title");
    auto preset_radiobox = Radiobox(&preset_labels, &selected_preset);
    auto input_width = Input(&width_str, "Width");
    auto input_height = Input(&height_str, "Height");
    auto input_pos_x = Input(&start_x_str, "Start X");
    auto input_pos_y = Input(&start_y_str, "Start Y");
    auto colour_depth_radiobox = Radiobox(&colour_depth_options, &selected_colour_depth);
    auto checkbox_fullscreen = Checkbox("Full Screen Mode", &is_fullscreen);
    auto checkbox_visible = Checkbox("Initially Visible", &is_visible);
    auto fit_monitor_btn = Button("Fit to Primary Display",
                                  [&]
                                  {
                                      width_str = std::to_string(primary_monitor_width);
                                      height_str = std::to_string(primary_monitor_height);
                                      selected_preset = static_cast<int>(presets.size()) - 1; // Custom
                                  });

    auto tab1_container = Container::Vertical({
        input_title,
        preset_radiobox,
        input_width,
        input_height,
        input_pos_x,
        input_pos_y,
        colour_depth_radiobox,
        checkbox_fullscreen,
        checkbox_visible,
        fit_monitor_btn,
    });

    // Update width & height when preset changes
    int last_preset = selected_preset;
    auto tab1_renderer = Renderer(tab1_container,
                                  [&]
                                  {
                                      if (selected_preset != last_preset)
                                      {
                                          last_preset = selected_preset;
                                          if (selected_preset >= 0 && selected_preset < static_cast<int>(presets.size()) - 1)
                                          {
                                              width_str = std::to_string(presets[selected_preset].width);
                                              height_str = std::to_string(presets[selected_preset].height);
                                          }
                                      }

                                      Elements monitor_elements;
                                      if (detected_monitors.empty())
                                      {
                                          monitor_elements.push_back(text("No external monitors enumerated") | dim);
                                      }
                                      else
                                      {
                                          for (auto const& m : detected_monitors)
                                          {
                                              monitor_elements.push_back(text("  • " + m) | color(Color::GreenLight));
                                          }
                                      }

                                      return vbox({
                                          hbox({
                                              // Left column: Window ID & Dimensions
                                              vbox({
                                                  text("Window Identity & Sizing") | bold | color(Color::Cyan),
                                                  separator(),
                                                  hbox(text("Title: ") | bold, input_title->Render() | border | size(WIDTH, GREATER_THAN, 25)),
                                                  separator(),
                                                  text("Resolution Presets:") | bold,
                                                  preset_radiobox->Render(),
                                                  separator(),
                                                  hbox({
                                                      text("Width:  ") | bold,
                                                      input_width->Render() | border | size(WIDTH, EQUAL, 10),
                                                      text("  Height: ") | bold,
                                                      input_height->Render() | border | size(WIDTH, EQUAL, 10),
                                                  }),
                                              }) | flex,
                                              separator(),
                                              // Right column: Position & Attributes
                                              vbox({
                                                  text("Placement & Mode") | bold | color(Color::Cyan),
                                                  separator(),
                                                  hbox({
                                                      text("Start X: ") | bold,
                                                      input_pos_x->Render() | border | size(WIDTH, EQUAL, 8),
                                                      text("  Start Y: ") | bold,
                                                      input_pos_y->Render() | border | size(WIDTH, EQUAL, 8),
                                                  }),
                                                  separator(),
                                                  text("Colour Depth:") | bold,
                                                  colour_depth_radiobox->Render(),
                                                  separator(),
                                                  checkbox_fullscreen->Render(),
                                                  checkbox_visible->Render(),
                                                  separator(),
                                                  text("Detected Displays:") | bold,
                                                  vbox(std::move(monitor_elements)),
                                                  fit_monitor_btn->Render(),
                                              }) | flex,
                                          }),
                                      });
                                  });

    // -- Tab 2: Render System Specific Settings
    auto cb_validation = Checkbox("Enable Validation Layers / Debug Runtime", &enable_validation);
    auto cb_debug_output = Checkbox("Enable Debug Output Messages", &enable_debug_output);
    auto cb_lowpower = Checkbox("Prefer Low-Power / Integrated GPU", &prefer_integrated_gpu);
    auto cb_tearing = Checkbox("Enable Tearing / Variable Refresh Rate", &enable_tearing);
    auto cb_dxil = Checkbox("Enable Modern DXIL Shader Compiler", &enable_dxil);
    auto cb_core = Checkbox("OpenGL Core Profile (vs Compatibility)", &core_profile);
    auto cb_vsync = Checkbox("Enable Vertical Sync (V-Sync)", &vsync);

    auto tab2_container = Container::Vertical({
        cb_validation,
        cb_debug_output,
        cb_lowpower,
        cb_tearing,
        cb_dxil,
        cb_core,
        cb_vsync,
    });

    auto tab2_renderer = Renderer(tab2_container,
                                  [&]
                                  {
                                      API current_api = availableSystems[selectedRenderSystem].api;
                                      Elements specific_options;

                                      if (current_api == API::Metal)
                                      {
                                          specific_options.push_back(cb_validation->Render());
                                          specific_options.push_back(cb_lowpower->Render());
                                          specific_options.push_back(cb_vsync->Render());
                                          specific_options.push_back(text("Note: Metal API validation enables GPU trace diagnostics in macOS.") | dim);
                                      }
                                      else if (current_api == API::Vulkan)
                                      {
                                          specific_options.push_back(cb_validation->Render());
                                          specific_options.push_back(cb_lowpower->Render());
                                          specific_options.push_back(cb_vsync->Render());
                                          specific_options.push_back(text("Note: Requires VK_LAYER_KHRONOS_validation installed on host.") | dim);
                                      }
                                      else if (current_api == API::OpenGL4)
                                      {
                                          specific_options.push_back(cb_core->Render());
                                          specific_options.push_back(cb_debug_output->Render());
                                          specific_options.push_back(cb_vsync->Render());
                                      }
                                      else if (current_api == API::D3D12)
                                      {
                                          specific_options.push_back(cb_validation->Render());
                                          specific_options.push_back(cb_dxil->Render());
                                          specific_options.push_back(cb_tearing->Render());
                                          specific_options.push_back(cb_vsync->Render());
                                      }

                                      return vbox({
                                          text("Configuring backend: " + availableSystems[selectedRenderSystem].name) | bold | color(Color::Cyan),
                                          text(availableSystems[selectedRenderSystem].description) | dim,
                                          separator(),
                                          vbox(std::move(specific_options)),
                                      });
                                  });

    // -- Tab 3: Visualisation Settings Components
    auto msaa_radiobox = Radiobox(&msaa_options, &selected_msaa);
    auto fps_radiobox = Radiobox(&fps_options, &selected_fps);
    auto theme_radiobox = Radiobox(&theme_options, &selected_theme);

    auto tab3_container = Container::Vertical({
        msaa_radiobox,
        fps_radiobox,
        theme_radiobox,
    });

    auto tab3_renderer = Renderer(tab3_container,
                                  [&]
                                  {
                                      return hbox({
                                          vbox({
                                              text("Multisample Anti-Aliasing (MSAA)") | bold | color(Color::Cyan),
                                              separator(),
                                              msaa_radiobox->Render(),
                                          }) | flex,
                                          separator(),
                                          vbox({
                                              text("Target Refresh Rate") | bold | color(Color::Cyan),
                                              separator(),
                                              fps_radiobox->Render(),
                                          }) | flex,
                                          separator(),
                                          vbox({
                                              text("Clear Color & Theme") | bold | color(Color::Cyan),
                                              separator(),
                                              theme_radiobox->Render(),
                                          }) | flex,
                                      });
                                  });

    // -- Tab 4: Summary & Launch Components
    auto launch_summary_btn = Button(
        "Launch Window",
        [&]
        {
            confirmed = true;
            screen.Exit();
        },
        ButtonOption::Animated(Color::Green));

    auto edit_summary_btn = Button("Return to Settings", [&] { activeTab = 0; });
    auto cancel_summary_btn = Button("Exit Without Launching", [&] { screen.Exit(); });

    auto tab4_container = Container::Horizontal({
        launch_summary_btn,
        edit_summary_btn,
        cancel_summary_btn,
    });

    auto tab4_renderer = Renderer(tab4_container,
                                  [&]
                                  {
                                      std::uint16_t const final_width = parseUInt16(width_str, initial.windowConfig.width);
                                      std::uint16_t const final_height = parseUInt16(height_str, initial.windowConfig.height);
                                      std::uint16_t const final_x = parseUInt16(start_x_str, initial.windowConfig.startX);
                                      std::uint16_t const final_y = parseUInt16(start_y_str, initial.windowConfig.startY);
                                      std::uint16_t const final_depth = (selected_colour_depth == 2 ? 16 : (selected_colour_depth == 1 ? 24 : 32));

                                      return vbox({
                                          text("Review Configuration Before Launch") | bold | color(Color::GreenLight),
                                          separator(),
                                          hbox({
                                              // Left Card: Render System & Window
                                              vbox({
                                                  text("Render Backend & Target:") | bold | color(Color::Cyan),
                                                  text("  • API:          " + availableSystems[selectedRenderSystem].name) | bold,
                                                  text("  • Window Title: " + window_title),
                                                  text("  • Resolution:   " + std::to_string(final_width) + " x " + std::to_string(final_height) + " px"),
                                                  text("  • Position:     (" + std::to_string(final_x) + ", " + std::to_string(final_y) + ")"),
                                                  text("  • Colour Depth: " + std::to_string(final_depth) + " bits"),
                                                  text(std::string("  • Fullscreen:   ") + (is_fullscreen ? "Yes" : "No")),
                                                  text(std::string("  • Visible:      ") + (is_visible ? "Yes" : "No")),
                                              }) | border |
                                                  flex,
                                              // Right Card: Vis & Features
                                              vbox({
                                                  text("Visualisation & Graphics Options:") | bold | color(Color::Cyan),
                                                  text(std::string("  • Validation:   ") + (enable_validation ? "Enabled" : "Disabled")),
                                                  text(std::string("  • V-Sync:       ") + (vsync ? "Enabled" : "Disabled")),
                                                  text(std::string("  • Low-Power:    ") + (prefer_integrated_gpu ? "Enabled" : "Disabled")),
                                                  text("  • Anti-Aliasing " + msaa_options[selected_msaa]),
                                                  text("  • Refresh Rate: " + fps_options[selected_fps]),
                                                  text("  • Clear Theme:  " + theme_options[selected_theme]),
                                              }) | border |
                                                  flex,
                                          }),
                                          separator(),
                                          hbox({
                                              launch_summary_btn->Render() | color(Color::GreenLight) | bold,
                                              text("  "),
                                              edit_summary_btn->Render(),
                                              text("  "),
                                              cancel_summary_btn->Render() | color(Color::RedLight),
                                          }) | center,
                                      });
                                  });

    // -- Tab 0 full renderer
    auto tab0_renderer = Renderer(tab0_container,
                                  [&]
                                  {
                                      return vbox({
                                          text("Select Active Graphics Render System:") | bold | color(Color::Cyan),
                                          separator(),
                                          hbox({
                                              vbox({
                                                  text("Available Hardware Backends:") | bold,
                                                  render_system_radiobox->Render(),
                                              }) | flex,
                                              separator(),
                                              vbox({
                                                  text("Backend Description:") | bold,
                                                  text(availableSystems[selectedRenderSystem].name) | bold | color(Color::Yellow),
                                                  separator(),
                                                  paragraph(availableSystems[selectedRenderSystem].description),
                                              }) | flex,
                                          }),
                                      });
                                  });

    // Master Tab Container
    auto tab_content = Container::Tab(
        {
            tab0_renderer,
            tab1_renderer,
            tab2_renderer,
            tab3_renderer,
            tab4_renderer,
        },
        &activeTab);

    // Global Menu & Navigation
    auto tabMenu = Menu(&tabTitles, &activeTab, MenuOption::HorizontalAnimated());
    auto prevBtn = Button(" < Previous ", [&] { activeTab = std::max(0, --activeTab); });
    auto nextBtn = Button(" Next > ", [&] { activeTab = std::min(++activeTab, static_cast<int>(tabTitles.size()) - 1); });
    auto launchBtn = Button(" Launch Window ",
                            [&]
                            {
                                confirmed = true;
                                screen.Exit();
                            });
    auto exitBtn = Button(" Cancel / Exit ",
                          [&]
                          {
                              confirmed = false;
                              screen.Exit();
                          });
    auto navBar = Container::Horizontal({prevBtn, nextBtn, launchBtn, exitBtn});
    auto main_layout = Container::Vertical({tabMenu, tab_content, navBar});

    auto root_renderer = Renderer(main_layout,
                                  [&]
                                  {
                                      return vbox({
                                                 // Header Banner
                                                 hbox({
                                                     text(" MORPHEUS ") | bold | inverted | color(Color::Cyan),
                                                     text(" Visualisation & Window Setup ") | bold | color(Color::White),
                                                     filler(),
                                                     text("[FTXUI] ") | dim,
                                                 }),
                                                 separator(),
                                                 // Tab Bar
                                                 tabMenu->Render() | center,
                                                 separator(),
                                                 // Page Content
                                                 tab_content->Render() | flex,
                                                 separator(),
                                                 // Bottom Controls
                                                 hbox({
                                                     prevBtn->Render(),
                                                     text(" "),
                                                     nextBtn->Render(),
                                                     filler(),
                                                     launchBtn->Render() | color(Color::GreenLight) | bold,
                                                     text(" "),
                                                     exitBtn->Render() | color(Color::RedLight),
                                                 }),
                                                 // Keyboard Help
                                                 hbox({
                                                     text("Keys: ") | dim,
                                                     text("← / → / Tab") | bold | color(Color::Cyan),
                                                     text(" Navigate Controls  |  ") | dim,
                                                     text("Space / Enter") | bold | color(Color::Cyan),
                                                     text(" Select/Toggle  |  ") | dim,
                                                     text("Esc") | bold | color(Color::RedLight),
                                                     text(" Cancel") | dim,
                                                 }) | center,
                                             }) |
                                             border;
                                  });

    // Escape handler
    auto root_with_events = CatchEvent(root_renderer,
                                       [&](Event event)
                                       {
                                           if (event == Event::Escape)
                                           {
                                               confirmed = false;
                                               screen.Exit();
                                               return true;
                                           }
                                           return false;
                                       });

    screen.Loop(root_with_events);

    if (!confirmed)
    {
        return std::nullopt;
    }

    VisualisationConfig result = initial;
    result.selectedApi = availableSystems[selectedRenderSystem].api;
    result.renderSystemName = availableSystems[selectedRenderSystem].name;

    result.windowConfig.windowName = window_title;
    result.windowConfig.width = parseUInt16(width_str, initial.windowConfig.width);
    result.windowConfig.height = parseUInt16(height_str, initial.windowConfig.height);
    result.windowConfig.startX = parseUInt16(start_x_str, initial.windowConfig.startX);
    result.windowConfig.startY = parseUInt16(start_y_str, initial.windowConfig.startY);
    result.windowConfig.colourDepth = (selected_colour_depth == 2 ? 16 : (selected_colour_depth == 1 ? 24 : 32));
    result.windowConfig.fullScreen = is_fullscreen;
    result.windowConfig.visible = is_visible;

    result.enableValidationLayers = enable_validation;
    result.enableDebugOutput = enable_debug_output;
    result.preferIntegratedGpu = prefer_integrated_gpu;
    result.enableTearing = enable_tearing;
    result.enableDxil = enable_dxil;
    result.coreProfile = core_profile;
    result.vsync = vsync;

    result.msaaSamples = msaa_values[selected_msaa];
    result.targetFps = fps_values[selected_fps];
    result.theme = theme_options[selected_theme];

    return result;
}

} // namespace morpheus::vis
