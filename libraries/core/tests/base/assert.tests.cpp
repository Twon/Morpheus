#include <morpheus/core/base/assert.hpp>
#include <morpheus/catch2/adapters/assert.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus
{

TEST_CASE("Ensure assert functionality works and is hooked into by the test framework", "[morpheus.base.assert]")
{
#ifdef MORPHEUS_ASSERT_ENABLED
    bool fired = false;
    setAssertHandler([&](Assertion assertion)
    {
        getPreviousHandler()(assertion);
        fired = true;
        return false;
    });
    MORPHEUS_ASSERT(false);
    REQUIRE(fired);
#endif // MORPHEUS_ASSERT_ENABLED
}

} // morpheus