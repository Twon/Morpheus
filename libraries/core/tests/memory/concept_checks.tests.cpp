#include "morpheus/core/memory/concepts/allocator.hpp"
#include "morpheus/core/memory/concepts/copier.hpp"
#include "morpheus/core/memory/concepts/deleter.hpp"
#include "morpheus/core/memory/concepts/nullable_pointer.hpp"
#include "morpheus/core/memory/default_copy.hpp"

#include <catch2/catch_all.hpp>

#include <memory>

namespace morpheus::memory::concepts
{

TEST_CASE("Verify memory concepts", "[morpheus.memory.concepts]")
{
    STATIC_REQUIRE(Copier<default_copy<char>, char>);
    STATIC_REQUIRE(Deleter<std::default_delete<char>, char>);

    SECTION("Nullable pointer checks pointers and fancy pointer types")
    {
        STATIC_REQUIRE(NullablePointer<void*>);
        STATIC_REQUIRE(NullablePointer<std::unique_ptr<void>>);
        STATIC_REQUIRE(NullablePointer<std::shared_ptr<void>>);
    }

    STATIC_REQUIRE(Allocator<std::allocator, int>);
}

} // namespace morpheus::memory::concepts
