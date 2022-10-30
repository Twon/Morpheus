#include <morpheus/core/base/assert.hpp>
#include <catch2/catch_all.hpp>

namespace morpheus
{

void enableCatch2AssertHooks()
{
    auto catch2AssertHandler = [](Assertion assertion)
    {
        ::Catch::AssertionHandler handler("MORPHEUS_ASSERT",::Catch::SourceLineInfo(assertion.location.file_name(), assertion.location.line()),
            assertion.expression.empty() ? assertion.expression.data() : "", ::Catch::ResultDisposition::Normal);

        handler.handleMessage(::Catch::ResultWas::ExplicitFailure, assertion.message);
        handler.setCompleted();
        return false;
    };
    setAssertHandler(std::move(catch2AssertHandler));
}

} // namespace morpheus