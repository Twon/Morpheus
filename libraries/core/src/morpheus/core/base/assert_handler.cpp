#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
#endif // #if (MORPHEUS_MODULES_SUPPORT)

#include "morpheus/core/base/assert_handler.hpp"
#include "morpheus/core/base/debugging.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/stacktrace.hpp"
#include "morpheus/core/conversion/adapters/std/stacktrace.hpp"


//#if (MORPHEUS_MODULES_SUPPORT)
//    import std;
//#else
    #include <iostream>
    #include <string_view>
    #include <utility>
//#endif // #if (MORPHEUS_MODULES_SUPPORT)

namespace morpheus
{

AssertHandler gAssertHandler = [](Assertion assertion)
{
    auto const debugMessage = fmt_ns::format("{}({}): assertion[{}]: {}\nBacktrace:{}\n", assertion.location.file_name(), assertion.location.line(),
                                             assertion.expression, assertion.message, MORPHEUS_CURRENT_STACKTRACE);
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

AssertHaltHandler gAssertHaltHandler = []()
{
    breakpoint();
};

AssertHaltHandler setAssertHaltHandler(AssertHaltHandler handler)
{
    auto previousHaltHandler = std::move(gAssertHaltHandler);
    gAssertHaltHandler = std::move(handler);
    return previousHaltHandler;
}

[[nodiscard]] AssertHaltHandler const& getAssertHaltHandler() { return gAssertHaltHandler; }

void assertHandler(AssertType type, sl_ns::source_location const location, std::string_view const expr, std::string_view message)
{
    if (type == AssertType::Assert)
    {
        if (getAssertHandler()(Assertion{location, expr, message}))
            getAssertHaltHandler()();
    }
    else
    {
        getAssertHandler()(Assertion{ location, expr, message });
        getAssertHaltHandler()();
    }
}

}
