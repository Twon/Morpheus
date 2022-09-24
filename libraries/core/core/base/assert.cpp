#include <core/base/assert.hpp>
#include <core/base/debugging.hpp>
#include <core/conformance/format.hpp>

#include <iostream>
#include <utility>

namespace morpheus
{

AssertHandler gAssertHandler = [](Assertion assertion)
{
    auto const debugMessage = fmt_ns::format("{}({}): assertion[{}]: {}", assertion.location.file_name(), assertion.location.line(), assertion.expression, assertion.message);
    debugPring(debugMessage);
    return true;
};

void setAssertHandler(AssertHandler handler)
{
    gAssertHandler = std::move(handler);
}

[[nodiscard]] AssertHandler const& getAssertHandler()
{
    return gAssertHandler;
}

void assertHandler(AssertType type, sl_ns::source_location const location, std::string_view const expr, std::string_view message)
{
    if (type == AssertType::Assert)
    {
        if (getAssertHandler()(Assertion{ location, expr, std::string(message) }))
            MORPHEUS_BREAKPOINT();
    }
    else
    {
        getAssertHandler()(Assertion{ location, expr, std::string(message) });
        MORPHEUS_BREAKPOINT();
    }
}

}