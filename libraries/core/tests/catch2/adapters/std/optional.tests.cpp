#include <morpheus/catch2/adapters/std/optional.hpp>

#include <catch2/catch_all.hpp>

#include <optional>

namespace morpheus
{

TEST_CASE("Test Catch2's display integration of std::optionabin/Debug/MorpheusCoreTestsl", "[morpheus.base.optinal]")
{
    std::optional<int> a(1), b;
    REQUIRE(a == b);
}

} // namespace morpheus
