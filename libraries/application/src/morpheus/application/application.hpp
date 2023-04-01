#pragma once

#include "morpheus/application/po/config.hpp"
#include "morpheus/application/po/options.hpp"

namespace morpheus::application
{

/// \class Application
///     The application class acts as a manager for a system of application components.  It is responsible for walking
///     the application graph to collect commandline parameters  
/// 
/// 
/// 
//template<typename T>
class Application {
public:

    /// 
    /// \param[in] argc The number of command line arguments.
    /// \param[in] argv List of command line arguments.
    auto commandline(int argc, char* argv[])
    {
        using namespace po;

        Config config;
        return parseProgramOptions(argc, argv, HelpDocumentation{}, config);
    }


    void run()
    {

    }
};

} // namespace morpheus::application