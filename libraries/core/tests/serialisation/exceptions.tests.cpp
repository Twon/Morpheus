#include "morpheus/core/serialisation/exceptions.hpp"

#include <catch2/catch_all.hpp>

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Serialisatoin exception helpers", "[morpheus.serialisation.exception.helpers]")
{
#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    #pragma warning(push)
    #pragma warning(disable : 4702) // unreachable code
#endif(MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)

    REQUIRE_THROWS_AS(throwBinaryException("Test binary exception"), BinaryException);
    REQUIRE_THROWS_AS(throwJsonException("Tesst Json exception"), JsonException);

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    #pragma warning(pop)
#endif(MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
}


} // namespace morpheus::serialisation
