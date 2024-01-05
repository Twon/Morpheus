#include "morpheus/core/conversion/enum.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>

namespace morpheus::conversion
{

enum class CardSuits : std::int32_t
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

TEST_CASE("Verify toString handling for enums", "[morpheus.conversion.enums.toString]")
{
    REQUIRE(toString(CardSuits::Hearts) == "Hearts");
    REQUIRE(toString(CardSuits::Diamonds) == "Diamonds");
    REQUIRE(toString(CardSuits::Clubs) == "Clubs");
    REQUIRE(toString(CardSuits::Spades) == "Spades");
}

TEST_CASE("Verify fromString handling for enums", "[morpheus.conversion.enums.fromString]")
{
    REQUIRE(fromString<CardSuits>("Hearts") == CardSuits::Hearts);
    REQUIRE(fromString<CardSuits>("Diamonds") == CardSuits::Diamonds);
    REQUIRE(fromString<CardSuits>("Clubs") == CardSuits::Clubs);
    REQUIRE(fromString<CardSuits>("Spades") == CardSuits::Spades);
}

} // namespace morpheus::conversion
