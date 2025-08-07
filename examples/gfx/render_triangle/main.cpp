#include <morpheus/application/application.hpp>
#include <morpheus/application/try_catch.hpp>
#include <morpheus/gfx/gl4/render_system.hpp>
#include <morpheus/gfx/platform/win32/render_window.hpp>
#include <morpheus/vis/render_system_factory.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace morpheus::application;
using namespace morpheus::gfx;

class RenderTriange : public Application
{
public:
    using Application::Application;

    RenderTriange(int argc, char const* const* argv)
    :   Application(argc, argv)
    ,   window(std::move(win32::RenderWindow::create(win32::RenderWindow::Config{})).value())
    {

    }

    void Run()
    {
        while (true)
        {
            //			#pragma FREEDOM_TODO( "Hide message pump behind Freedom operating system abstraction")

            ::MSG msg;
            ::ZeroMemory(&msg, sizeof(msg));

            // While there is messages in the queue pump them
            // till the message queue until it is empty
            while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            {
                if (::GetMessage(&msg, NULL, 0, 0))
                {
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                }
            }
        }
    }

protected:
    win32::RenderWindow window;
};

int main(int argc, char* argv[])
{
    //const std::vector<std::string> renders = {
    //    "Direct X 12",
    //    "OpenGL 4",
    //    "Vulkan"
    //};

    //int selectedRenders = 0;
    //ftxui::Component compiler = ftxui::Radiobox(&renders, &selectedRenders);

    //auto screen = ftxui::ScreenInteractive::Fullscreen();
    ////auto testComponent = ftxui::Renderer([]() { return ftxui::text("test Component"); });
    //auto testComponent = ftxui::Renderer(compiler, [&]() {
    //    auto rendererWin = ftxui::window(ftxui::text("Renderer"), compiler->Render() | ftxui::vscroll_indicator | ftxui::frame);
    //    return rendererWin;
    //});
    //screen.Loop(testComponent);

    morpheus::vis::RenderSystemFactory factory;
    factory.runTuiConfiguration();

    //tryCatch(
    //    [&]
    //    {
    //        RenderTriange example(argc, argv);
    //        example.Run();
    //    });

    //    render_system_factory renderer_factory;
}

/*
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace ftxui;

// Enum to track the current screen state
enum class ScreenStage {
    SelectRenderer,
    ConfigureRenderer,
};

int main() {
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();

    // State
    ScreenStage current_stage = ScreenStage::SelectRenderer;

    std::vector<std::string> renderer_options = {
        "DirectX 12", "Vulkan", "OpenGL"
    };
    int selected_renderer = 0;
    auto renderer_selector = Radiobox(&renderer_options, &selected_renderer);

    // Settings per renderer
    std::map<std::string, std::vector<std::string>> renderer_settings = {
        {"DirectX 12", {"Use DXIL", "Enable Tearing"}},
        {"Vulkan", {"Validation Layers", "Prefer Integrated GPU"}},
        {"OpenGL", {"Core Profile", "Enable Debug Output"}}
    };

    // Dynamic state for second screen
    std::vector<std::string> setting_labels;
    std::vector<bool> setting_states;  // Real bools for safety
    std::vector<Component> setting_checkboxes;
    Component settings_container = Container::Vertical({});

    // Component placeholders
    Component next_button, back_button, finish_button;

    // Container that will switch content
    Component main_container = Container::Vertical({});

    // Renderer root
    Component root = Renderer(main_container, [&] {
        if (current_stage == ScreenStage::SelectRenderer) {
            return vbox({
                text("Select Render System:") | bold,
                renderer_selector->Render(),
                separator(),
                next_button->Render(),
            }) | border | center;
        }
        else {
            Elements checkbox_elements;
            for (auto& cb : setting_checkboxes) {
                checkbox_elements.push_back(cb->Render());
            }

            return vbox({
                text("Configure Settings for: ") | bold,
                text(renderer_options[selected_renderer]),
                separator(),
                vbox(std::move(checkbox_elements)),
                separator(),
                hbox({
                    back_button->Render(),
                    finish_button->Render(),
                }) | center
            }) | border | center;
        }
    });

    // Buttons — defined after root to capture state
    next_button = Button("Next", [&] {
        current_stage = ScreenStage::ConfigureRenderer;

        // Populate setting labels + bools
        std::string selected_name = renderer_options[selected_renderer];
        setting_labels = renderer_settings[selected_name];
        setting_states = std::vector<bool>(setting_labels.size(), false);
        setting_checkboxes.clear();

        for (size_t i = 0; i < setting_labels.size(); ++i) {
            bool local = setting_states[i];
            setting_checkboxes.push_back(Checkbox(setting_labels[i], &local));
        }

        settings_container = Container::Vertical(setting_checkboxes);

        // Reconfigure main container
        main_container->DetachAllChildren();
        //main_container->Add(renderer_selector);
        main_container->Add(settings_container);
        main_container->Add(back_button);
        main_container->Add(finish_button);

        screen.PostEvent(Event::Custom);  // force re-render
    });

    back_button = Button("Back", [&] {
        current_stage = ScreenStage::SelectRenderer;
        main_container->DetachAllChildren();
        main_container->Add(renderer_selector);
        main_container->Add(next_button);
        screen.PostEvent(Event::Custom);  // force re-render
    });

    finish_button = Button("Finish", [&] {
        screen.Exit();
    });

    // Initial container setup
    main_container->Add(renderer_selector);
    main_container->Add(next_button);

    screen.Loop(root);
    return 0;
}
*/
