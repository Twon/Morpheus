#include "morpheus/core/serialisation/exceptions.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Serialisatoin exception helpers", "[morpheus.serialisation.exception.helpers]")
{
    REQUIRE_THROWS_AS(throwBinaryException("Tesst binary exception"), BinaryException);
    REQUIRE_THROWS_AS(throwJsonException("Tesst Json exception"), JsonException);
}


} // namespace morpheus::serialisation
