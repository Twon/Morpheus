#pragma once

#include <morpheus/gfx/platform/render_window.hpp>
#include <morpheus/vis/render_system_factory.hpp>

#include <optional>
#include <string>

namespace morpheus::vis
{

/// \struct VisualisationConfig
///     Configuration options for setting up a window using a visualisation system
///     configured with a specific render system.
struct VisualisationConfig
{
    API selectedApi = API::Metal;           ///< The graphics API selected for the render system.
    std::string renderSystemName = "Metal"; ///< The display name of the selected render system.

    gfx::WindowConfig windowConfig; ///< The underlying window configuration options.

    bool enableValidationLayers = false; ///< Enable API validation layers or debug runtime.
    bool enableDebugOutput = false;      ///< Enable debug message output.
    bool preferIntegratedGpu = false;    ///< Prefer integrated / low-power GPU over discrete GPU.
    bool enableTearing = false;          ///< Enable tearing / variable refresh rate (VRR).
    bool enableDxil = false;             ///< Enable modern DXIL shader compiler for D3D12.
    bool coreProfile = true;             ///< Use OpenGL Core Profile rather than Compatibility Profile.

    bool vsync = true;                ///< Enable vertical synchronization.
    int msaaSamples = 1;              ///< Multisample anti-aliasing sample count (1 = off, 2, 4, 8).
    int targetFps = 60;               ///< Target frame rate limit (e.g. 30, 60, 120, 144, 0 = unlimited).
    std::string theme = "Dark Slate"; ///< Viewport theme / clear colour profile.
};

/// \class Tui
///     Terminal User Interface runner for configuring visualisation options.
class Tui
{
public:
    /// Run the interactive terminal UI to configure window and visualisation options.
    /// \param[in] initial
    ///     The initial configuration options.
    /// \return std::optional containing the configured VisualisationConfig if confirmed,
    ///         or std::nullopt if cancelled.
    static auto run(VisualisationConfig const& initial = {}) -> std::optional<VisualisationConfig>;
};

} // namespace morpheus::vis
