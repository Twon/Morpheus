#include <gl4/wgl/adapter.hpp>
#include <catch2/catch.hpp>

namespace morpheus::test
{
using namespace morpheus::gfx::gl4::wgl;

TEST_CASE("Create an adapter mode list", "[morpheus.core.gfx.adapter_list]")
{
}

TEST_CASE("Iterates over the adapters in the list", "[morpheus.core.gfx.adapter_list]")
{
    GIVEN("An adapter list")
    {
        //adapter_list adapters;
        THEN("Loop over all adapters using native for loop syntax")
        {
            for (auto& adapter : enumerateAdapters())
            {
                INFO("The adapter id is: " << adapter.getId());
            }
        }
    }
}

} // namespace morpheus::test
