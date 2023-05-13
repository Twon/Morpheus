#include "morpheus/core/base/verify.hpp"

#include <catch2/catch_all.hpp>
#include <magic_enum.hpp>
#include <cstdint>
 
namespace morpheus
{

enum class TrafficLights : std::int32_t
{
    Red,
    Yellow,
    Green,
};

TEST_CASE("Ensure magic enum integrates with the Morpheus framework", "[morpheus.enum.name]")
{
    REQUIRE(magic_enum::enum_name(TrafficLights::Red) == "Red");
    REQUIRE(magic_enum::enum_name(TrafficLights::Yellow) == "Yellow");
    REQUIRE(magic_enum::enum_name(TrafficLights::Green) == "Green");
}

TEST_CASE("Ensure magic enum converts string to enums", "[morpheus.enum.from_string]")
{
    REQUIRE(magic_enum::enum_cast<TrafficLights>("Red") == TrafficLights::Red);
    REQUIRE(magic_enum::enum_cast<TrafficLights>("Yellow") == TrafficLights::Yellow);
    REQUIRE(magic_enum::enum_cast<TrafficLights>("Green") == TrafficLights::Green);
}

} // morpheus