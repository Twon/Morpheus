#include "morpheus/core/memory/concepts/copier.hpp"
#include "morpheus/core/memory/concepts/deleter.hpp"
#include "morpheus/core/memory/default_copy.hpp"

#include <catch2/catch_all.hpp>

#include <memory>

namespace morpheus::memory::concepts
{

TEST_CASE("Verify memory concepts", "[morpheus.memory.concepts]")
{
    STATIC_REQUIRE(Copier<default_copier, char>);
    STATIC_REQUIRE(Deleter<std::default_deleter, char>);
}

} // namespace morpheus::memory::concepts
