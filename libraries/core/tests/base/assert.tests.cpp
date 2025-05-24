#include <morpheus/catch2/adapters/assert.hpp>
#include <morpheus/core/base/assert.hpp>
#include <morpheus/core/base/assert_handler.hpp>
#include <morpheus/core/base/scoped_action.hpp>
#include <morpheus/redirect_stream.hpp>

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string_view>

namespace morpheus
{

TEST_CASE("Ensure assert functionality works and is hooked into by the test framework", "[morpheus.base.assert]")
{
#ifdef MORPHEUS_ASSERT_ENABLED
    bool fired = false;
    AssertHandler const currentHandler = getAssertHandler();

    auto const onEntry = [&]
    {
        setAssertHandler(
            [&](Assertion assertion)
            {
                getPreviousHandler()(assertion);
                fired = true;
                return false;
            });
    };

    auto const onExit = [&](){ setAssertHandler(currentHandler); };
    ScopedAction const restoreAssertHandler(onEntry, onExit);

    RedirectStream captureOutStream(std::cout);
    RedirectStream captureErrorStream(std::cerr);

    MORPHEUS_ASSERT(false);
    REQUIRE(fired);
#endif // MORPHEUS_ASSERT_ENABLED
}

TEST_CASE("Ensure assert functionality responds to appropriate defines", "[morpheus.base.assert.disabled_conditions]")
{
#if defined(NDEBUG)
    MORPHEUS_ASSERT(false);
#endif

#define MORPHEUS_DISABLE_ASSERT
    MORPHEUS_ASSERT(true);
#undef MORPHEUS_DISABLE_ASSERT
}

} // namespace morpheus
