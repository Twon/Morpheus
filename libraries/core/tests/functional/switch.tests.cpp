#include "morpheus/core/functional/switch.hpp"

#include <magic_enum_format.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::functional
{

TEST_CASE("", "[morpheus.functional.switch.enum]")
{
    enum class Case
    {
        A,
        B,
        C,
        D
    };
    using Cases = CaseList<SwitchCase<Case, Case::A>, SwitchCase<Case, Case::B>, SwitchCase<Case, Case::C>, SwitchCase<Case, Case::D>>;
    STATIC_REQUIRE(boost::mp11::mp_size<Cases>::value == magic_enum::enum_count<Case>());
    magic_enum::enum_for_each<Case>([](auto const caseToCall)
                                    { switch_(caseToCall, Cases{}, [&](auto const executedCase) { REQUIRE(caseToCall == executedCase); }); });
}

} // namespace morpheus::functional