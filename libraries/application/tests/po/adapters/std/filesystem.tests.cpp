#include "morpheus/application/po/adapters/std/filesystem.hpp" // IWYU pragma: keep
#include "morpheus/application/po/options.hpp"
#include "morpheus/application/version.hpp"
#include "morpheus/logging.hpp"

#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>

namespace morpheus::application::po
{

struct Filesystem
{
    std::filesystem::path path;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("path", po::value(&path), "The location of the path.");
        // clang-format on
    }
};

TEST_CASE_METHOD(LoggingFixture, "Test parsing of std filesystem path as options", "[morpheus.application.po.adapters.std.filesystem]")
{
    SECTION("Ensure valid value parse correctly")
    {
        auto getPath = [](std::string_view param)
        {
            Filesystem filesystem{};
            std::array cliOptions = {"dummyProgram.exe", "--path", param.data()};
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, filesystem);
            REQUIRE(!result);
            return filesystem.path;
        };

        auto const exeLocation = boost::dll::program_location().parent_path();
        REQUIRE(getPath(".") == std::filesystem::path("."));
        REQUIRE(getPath("..") == std::filesystem::path(".."));
        REQUIRE(getPath(exeLocation.string()) == exeLocation);
        REQUIRE(getPath((exeLocation / ".").lexically_normal().string()) != exeLocation); // Not the same, depends on context: https://stackoverflow.com/questions/42952605/boostfilesystempathlexically-normal-is-this-incorrect-behavior
        if (exeLocation.has_parent_path())
            REQUIRE(getPath((exeLocation / "..").lexically_normal().string()) == exeLocation.parent_path());

        // https://github.com/boostorg/program_options/issues/69
        REQUIRE(getPath("/home/user/path with spaces/.") == std::filesystem::path("/home/user/path with spaces/."));
    }
}

} // namespace morpheus::application::po
