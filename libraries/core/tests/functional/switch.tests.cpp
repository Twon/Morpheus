#include "morpheus/core/functional/switch.hpp"

#include <boost/hana/size.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip.hpp>
#include <boost/mp11.hpp>
#include <catch2/catch_all.hpp>
#include <magic_enum_format.hpp>

#include <tuple>

namespace hana = boost::hana;
using namespace hana::literals;

namespace morpheus::functional
{

/*
// clang-format off
struct ReturnLValueReference
{
    bool a;
    char b;
    int c;
    float d;

    bool& operator()(bool) { return a; }
    char& operator()(char) { return b; }
    int& operator()(int) { return c; }
    float& operator()(float) { return d; }
};

// struct ReturnRValueReference
// {
//     std::tuple<bool, char, int, float> values;

//     bool&& operator()(bool) { return std::get<0>(values); }
//     char&& operator()(char) { return std::get<1>(values); }
//     int&& operator()(int) { return std::get<2>(values); }
//     float&& operator()(float) { return std::get<3>(values); }
// };

// clang-format on

TEST_CASE("Verify switch cases returning a value", "[morpheus.functional.switch.value]")
{
    using Cases = CaseList<SwitchCase<int, 0>, SwitchCase<int, 1>, SwitchCase<int, 2>, SwitchCase<int, 3>>;
    STATIC_REQUIRE(boost::mp11::mp_size<Cases>::value == 4);
    for (int i = 0; i < boost::mp11::mp_size<Cases>::value; ++i) {
        auto const result = switch_(i, Cases{},
                                    [](auto const caseValue)
                                    {
                                        return caseValue;
                                    });
        REQUIRE(result == i);
    }
}

TEST_CASE("Verify switch cases returning a lvalue-reference", "[morpheus.functional.switch.lvalue_reference]")
{
    // auto types = boost::hana::tuple_t<bool, char, int, float>;
    // auto caseValues = []<std::size_t... Is>(std::index_sequence<Is...>)
    // {
    //     return boost::hana::tuple_c<std::size_t, Is...>;
    // }(std::make_index_sequence<boost::hana::size(types)>());
    // auto caseParams = boost::hana::zip(types, caseValues);
    // auto cases = boost::hana::transform(caseParams,
    //                                     [](auto const params)
    //                                     {
    //                                         return SwitchCase<decltype(+params[1_c]), +params[1_c], decltype(params[0_c])>;
    //                                     });

    // using CaseTypes = std::tuple<bool, char, int, float>;
    // using CaseValues = boost::mp11::mp_iota_c<4>;
    // using Case = boost::hana::transform
    // using Cases = boost::mp11::mp_transform<

    using Cases = CaseList<SwitchCase<int, 0, bool>, SwitchCase<int, 1, char>, SwitchCase<int, 2, int>, SwitchCase<int, 3, float>>;
    STATIC_REQUIRE(boost::mp11::mp_size<Cases>::value == 4);

    ReturnLValueReference expected;
    auto const& result = switch_(3, Cases{}, std::ref(expected));
    REQUIRE(&result == &expected.d);
}

TEST_CASE("Verify switch cases returning a rvalue-reference", "[morpheus.functional.switch.rvalue_reference]") {}
*/

TEST_CASE("Enumerate switch cases for each enum entry", "[morpheus.functional.switch.enum]")
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
    magic_enum::enum_for_each<Case>(
        [](auto const caseToCall)
        {
            switch_(caseToCall, Cases{},
                    [&](auto const executedCase)
                    {
                        REQUIRE(caseToCall == executedCase);
                    });
        });
}

} // namespace morpheus::functional