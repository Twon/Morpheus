#include <morpheus/gfx/vulkan/adapter.hpp>
#include <morpheus/gfx/platform/concepts/adapter.hpp>
#include <catch2/catch_all.hpp>

namespace morpheus::gfx::vulkan
{

TEST_CASE("Concept checks for vulkan adapters", "[morpheus.gfx.vulkan.adapter.concepts]")
{
    STATIC_REQUIRE(gfx::concepts::VideoMode<VideoMode>);
    STATIC_REQUIRE(gfx::concepts::Adapter<Adapter>);
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

} // namespace morpheus::gfx::vulkan
