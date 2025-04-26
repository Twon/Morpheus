#include <morpheus/catch2/adapters/assert.hpp>
#include <catch2/catch_all.hpp>

#include <utility>

namespace morpheus
{

AssertHandler previousHandler;

const AssertHandler& getPreviousHandler()
{
    return previousHandler;
}

void enableCatch2AssertHooks()
{
    auto catch2AssertHandler = [](Assertion assertion)
    {
        // This is only called when an assert fires in test which should never happen, so disable code coverage.
        // LCOV_EXCL_START
        ::Catch::AssertionHandler handler("MORPHEUS_ASSERT",::Catch::SourceLineInfo(assertion.location.file_name(), assertion.location.line()),
            assertion.expression.empty() ? assertion.expression.data() : "", ::Catch::ResultDisposition::Normal);

        handler.handleMessage(::Catch::ResultWas::ExplicitFailure, std::string(assertion.message));
        handler.complete();
        return false;
        // LCOV_EXCL_STOP
    };
    previousHandler = setAssertHandler(std::move(catch2AssertHandler));
}

} // namespace morpheus
