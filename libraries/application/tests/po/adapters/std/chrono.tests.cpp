#include "morpheus/application/application.hpp"
#include "morpheus/application/po/adapters/std/chrono.hpp"
#include "morpheus/core/serialisation/adapters/std/chrono.hpp"

#include <catch2/catch_test_macros.hpp>

#include <chrono>

namespace morpheus::application::po
{

template <serialisation::detail::IsStdChronoDuration Duration>
struct ChronoDuration
{
    Duration duration;

    void addOptions(boost::program_options::options_description& options)
    {
        namespace po = boost::program_options;
        // clang-format off
        options.add_options()
            ("duration", po::value(&duration), "The time duration.");
        // clang-format on
    }
};

TEST_CASE("Test parsing of std chrono duration", "[morpheus.application.po.adapters.std.chrono.duration]")
{
    SECTION("Ensure valid value parse correctly")
    {
        auto getDuration = []<serialisation::detail::IsStdChronoDuration Duration>(std::string_view param)
        {
            ChronoDuration<Duration> durationOptions{};
            std::array cliOptions = {"dummyProgram.exe", "--duration", param.data()};
            auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, durationOptions);
            REQUIRE(!result);
            return durationOptions.duration;
        };

        REQUIRE(getDuration.template operator()<std::chrono::nanoseconds>("5000ns") == std::chrono::nanoseconds{5000});
        REQUIRE(getDuration.template operator()<std::chrono::microseconds>("987us") == std::chrono::microseconds{987});
        REQUIRE(getDuration.template operator()<std::chrono::milliseconds>("1382ms") == std::chrono::milliseconds{1382});
        REQUIRE(getDuration.template operator()<std::chrono::seconds>("30s") == std::chrono::seconds{30});
        REQUIRE(getDuration.template operator()<std::chrono::minutes>("60min") == std::chrono::minutes{60});
        REQUIRE(getDuration.template operator()<std::chrono::hours>("48h") == std::chrono::hours{48});
        REQUIRE(getDuration.template operator()<std::chrono::weeks>("52w") == std::chrono::weeks{52});
        REQUIRE(getDuration.template operator()<std::chrono::years>("50y") == std::chrono::years{50});
        REQUIRE(getDuration.template operator()<std::chrono::months>("1m") == std::chrono::months{1});
    }
    SECTION("Ensure invalid value parse correctly")
    {
        std::array cliOptions = {"dummyProgram.exe", "--duration", "invalid"};
        ChronoDuration<std::chrono::nanoseconds> durationOptions{};
        auto const result = parseProgramOptions(static_cast<int>(cliOptions.size()), cliOptions.data(), HelpDocumentation{}, durationOptions);
        REQUIRE(result);
    }
}

} // namespace morpheus::application::po
