#include <morpheus/catch2/adapters/assert.hpp>
#include <morpheus/core/base/verify.hpp>
#include <morpheus/core/base/scoped_action.hpp>
#include <morpheus/redirect_stream.hpp>

#include <catch2/catch_all.hpp>

#include <iostream>

namespace morpheus
{

TEST_CASE("Ensure assert functionality responds to appropriate defines", "[morpheus.base.verity]")
{
    bool fired = false;
    auto const currentHandler = getAssertHandler();

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

    auto const onExit = [&]() { setAssertHandler(currentHandler); };
    ScopedAction const restoreAssertHandler(onEntry, onExit);

    bool haltFired = false;
    auto const currentHaltHandler = getAssertHaltHandler();
    auto const onHaltEntry = [&]
    {
        setAssertHaltHandler(
            [&]()
            {
                haltFired = true;
            });
    };

    auto const onHaltExit = [&]() { setAssertHaltHandler(currentHaltHandler); };
    ScopedAction const restoreAssertHaltHandler(onHaltEntry, onHaltExit);

    RedirectStream captureOutStream(std::cout);
    RedirectStream captureErrorStream(std::cerr);

    MORPHEUS_VERIFY(false);
    REQUIRE(fired);
    REQUIRE(haltFired);
}

} // morpheus
