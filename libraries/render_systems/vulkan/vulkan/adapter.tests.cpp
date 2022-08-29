#include <vulkan/adapter.hpp>
#include <catch2/catch_all.hpp>

namespace morpheus::test
{
using namespace morpheus::gfx;

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.adapter_list]")
{
}

TEST_CASE("Iterates over the adapters in the list", "[morpheus.gfx.vulkan.adapters]")
{
    GIVEN("An adapter list")
    {
        //adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
//            for (auto& adapter : enumerateAdapters())
            {
//                INFO("The adapter id is: " << adapter.getId());
            }
        }
    }
}

} // namespace morpheus::test
