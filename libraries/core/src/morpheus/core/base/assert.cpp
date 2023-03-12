#include <morpheus/core/base/assert.hpp>
#include <morpheus/core/base/debugging.hpp>
#include <morpheus/core/conformance/format.hpp>

#include <iostream>
#include <utility>

namespace morpheus
{

AssertHandler gAssertHandler = [](Assertion assertion)
{
    auto const debugMessage = fmt_ns::format("{}({}): assertion[{}]: {}", assertion.location.file_name(), assertion.location.line(), assertion.expression, assertion.message);
    debugPrint(debugMessage);
    return true;
};

AssertHandler setAssertHandler(AssertHandler handler)
{
    auto previousHandler = std::move(gAssertHandler);
    gAssertHandler = std::move(handler);
    return previousHandler;
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
            breakpoint();
    }
    else
    {
        getAssertHandler()(Assertion{ location, expr, std::string(message) });
        breakpoint();
    }
}

}