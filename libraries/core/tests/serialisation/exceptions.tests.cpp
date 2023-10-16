#include "morpheus/core/serialisation/exceptions.hpp"

#include <catch2/catch_all.hpp>

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    #pragma warning(push)
    // unreachable code
    #pragma warning(disable : 4702)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)

using namespace Catch;

namespace morpheus::serialisation
{

TEST_CASE("Serialisatoin exception helpers", "[morpheus.serialisation.exception.helpers]")
{
    REQUIRE_THROWS_AS(throwBinaryException("Test binary exception"), BinaryException);
    REQUIRE_THROWS_AS(throwJsonException("Tesst Json exception"), JsonException);
}


} // namespace morpheus::serialisation

#if (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
    #pragma warning(pop)
#endif // (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)
