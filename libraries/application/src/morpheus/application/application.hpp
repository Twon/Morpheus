#pragma once

#include "morpheus/application/po/config.hpp"
#include "morpheus/application/po/options.hpp"

#include <filesystem>

namespace morpheus::application
{

/// \class Application
///     The application class acts as a manager for a system of application components.  It is responsible for walking
///     the application graph to initialised all components before entering the main loop.  When walking the component
///     graph all commandline parameters will be collected and and sent for initialisation via input parameters.
///
///
///
// template<typename T>
class Application {
public:
    ///
    /// \param[in] argc The number of command line arguments.
    /// \param[in] argv List of command line arguments.
    Application(int argc, char const* const* argv);

    /// Application command line configuration.
    po::Config const& getConfig() const noexcept { return mConfig; }

    /// Path to application log file.
    std::filesystem::path getLogPath() const noexcept { return mLogPath; }

    void run()
    {

    }

private:
    po::Config mConfig; /// Common application configuration
    std::filesystem::path mLogPath; /// Path to application log file.
};

} // namespace morpheus::application
