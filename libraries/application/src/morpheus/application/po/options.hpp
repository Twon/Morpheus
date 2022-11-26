#pragma once

#include <morpheus/application/version.hpp>
#include <morpheus/core/conformance/format.hpp>
#include <morpheus/core/conformance/print.hpp>

#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

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

/// \class HelpDocumentation
///     
struct HelpDocumentation
{
    std::string_view name;
    std::string_view synopsis;
    std::optional<Version> version;
};

//std::optional<int> parseProgramOptions(std::span<char*> parameters, HelpDocumentation msgDetails, CustomProgramOptions auto&... options)
//{
//    return parseProgramOptions(static_cast<int>(parameters.size()), parameters.data(), std::move(msgDetails), options...);
//}

std::optional<int> parseProgramOptions(int argc, char const* const* argv, HelpDocumentation msgDetails, CustomProgramOptions auto&... options)
{
    return parseProgramOptions(std::span<char const * const>{argv, static_cast<std::size_t>(argc)}, std::move(msgDetails), options...);
}

std::optional<int> parseProgramOptions(std::span<char const * const> parameters, HelpDocumentation msgDetails, CustomProgramOptions auto&... options)
{
    namespace po = boost::program_options;
    try
    {
        auto const version = (msgDetails.version) ? fmt_ns::format("version {}", *msgDetails.version) : std::string();
        po::options_description desc(fmt_ns::format(
            "{}\n{} \n\nUsage: ",
            std::filesystem::path(parameters[0]).filename().string(), version));

        desc.add_options()("help", "Display help message");

        (options.addOptions(desc), ...);

        po::variables_map vm;
        po::store(po::parse_command_line(static_cast<int>(parameters.size()), parameters.data(), desc), vm);

        if (vm.count("help"))
        {
            desc.print(std::cout);
            return 1;
        }

        po::notify(vm);
    }
    catch (po::required_option& e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what() << std::endl;
        return 1;
    }
    return std::nullopt;
}


} // namespace morpheus::application::po