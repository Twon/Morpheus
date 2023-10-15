#include "morpheus/core/serialisation/exceptions.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Serialisatoin exception helpers", "[morpheus.serialisation.exception.helpers]")
{
#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code
    REQUIRE_THROWS_AS(throwBinaryException("Test binary exception"), BinaryException);
    REQUIRE_THROWS_AS(throwJsonException("Tesst Json exception"), JsonException);
#pragma warning(pop)
}


} // namespace morpheus::serialisation
