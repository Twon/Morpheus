#include <core/gfx/adapters/adapter_list.hpp>
#include <catch2/catch.hpp>

namespace morpheus::test
{
using namespace morpheus::gfx;

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.adapter_list]")
{
}

TEST_CASE("Iterates over the adapters in the list", "[morpheus.core.gfx.adapter_list]")
{
    GIVEN("An adapter list")
    {
        adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
            for (const auto& adapter : adapters)
            {

            }
        }
    }
}

} // namespace morpheus::test
