#include "morpheus/core/meta/complete.hpp"
#include "morpheus/core/meta/concepts/complete.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::meta
{

class IncompleteType;

class CompleteEmptyType {};

class CompleteType
{
    CompleteType() = default;

    int member = 0;
};

TEST_CASE("Meta is complete allows the compile time detection of complete types", "[morpheus.meta.is_complete]")
{
    STATIC_REQUIRE(!meta::is_complete_v<IncompleteType>);
    STATIC_REQUIRE(meta::is_complete_v<CompleteEmptyType>);
    STATIC_REQUIRE(meta::is_complete_v<CompleteType>);
}

TEST_CASE("Meta is complete concept check detection of complete types", "[morpheus.meta.concepts.is_complete]")
{
    STATIC_REQUIRE(!meta::concepts::IsComplete<IncompleteType>);
    STATIC_REQUIRE(meta::concepts::IsComplete<CompleteEmptyType>);
    STATIC_REQUIRE(meta::concepts::IsComplete<CompleteType>);
}

} // namespace morpheus::meta
