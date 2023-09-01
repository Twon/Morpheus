#include "morpheus/core/conformance/date.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/adapters/std/expected.hpp"

#include <catch2/catch_all.hpp>

#include <chrono>

namespace morpheus::serialisation
{

TEST_CASE("Verify std::format specialisation for std::chrono::duration", "[morpheus.conversion.chrono.duration.formatter]")
{
    REQUIRE(fmt_ns::format("{}", std::chrono::nanoseconds{45}) == "45ns");
}

} // namespace morpheus::serialisation