#pragma once

#include <morpheus/application/version.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <boost/dll.hpp>
#include <boost/log/trivial.hpp>

#if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnull-dereference"
#endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)

#include <boost/program_options.hpp>

#if (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)
    #pragma GCC diagnostic pop
#endif // (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)

#include <iostream>
#include <filesystem>
#include <optional>
#include <span>

namespace morpheus::application::po
{

// clang-format off
template<typename T>
concept CustomProgramOptions = requires(T& t, boost::program_options::options_description& options)
{
    { t.addOptions(options) } -> std::same_as<void>;
};
// clang-format on

/// \struct HelpDocumentation
///     Holds common help documentation information for applications.
struct HelpDocumentation
{
    std::string_view name; ///< The name of the application, typically the executable name.
    std::string_view synopsis; ///< A brief synopsis of the application, typically a one-liner describing its purpose.
    std::optional<Version> version; ///< The version of the application, if available.
};

std::optional<int> parseProgramOptions(int argc, char const* const* argv, HelpDocumentation const& msgDetails, CustomProgramOptions auto&... options)
{
    return parseProgramOptions(std::span<char const * const>{argv, static_cast<std::size_t>(argc)}, msgDetails, options...);
}

std::optional<int> parseProgramOptions(std::span<char const * const> parameters, HelpDocumentation const& msgDetails, CustomProgramOptions auto&... options)
{
    namespace po = boost::program_options;
    try
    {
        auto const version = (msgDetails.version) ? fmt_ns::format("version {}", *msgDetails.version) : std::string();
        po::options_description desc(fmt_ns::format("{}\n{} \n\nUsage: ", boost::dll::program_location().stem().string(), version));

        desc.add_options()("help,h", "Display the application help message.");

        if (msgDetails.version)
            desc.add_options()("version,v", "Display the application version.");

        (options.addOptions(desc), ...);

        po::variables_map vm;
        po::store(po::parse_command_line(static_cast<int>(parameters.size()), parameters.data(), desc), vm);

        if (vm.count("help"))
        {
            desc.print(std::cout);
            return 1;
        }

        if (msgDetails.version && vm.count("version"))
        {
            auto const output = fmt_ns::format("{} {}", boost::dll::program_location().stem().string(), *msgDetails.version);
            print_ns::print("{}", output);
            return 1;
        }

        po::notify(vm);
    }
    catch (po::error_with_option_name& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what() << std::endl;
        return 1;
    }
    catch (po::error& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what() << std::endl;
        return 1;
    }
    return std::nullopt;
}


} // namespace morpheus::application::po
