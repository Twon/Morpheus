#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/meta/concepts/scannable.hpp"

#include <catch2/catch_test_macros.hpp>

#include <tuple>

struct ScannableType
{
    int first = 0;
    double second = 0.0;
};

template <>
struct morpheus::conf::scan::scanner<ScannableType> : morpheus::conf::scan::scanner<std::string>
{
    template <typename Context>
    auto scan(ScannableType& val, Context& ctx) const -> morpheus::conf::scan::scan_expected<typename Context::iterator>
    {
        return morpheus::conf::scan::scan<int, double>(ctx.range(), "[{}, {}]")
            .transform(
                [&val](auto const& result)
                {
                    std::tie(val.first, val.second) = result.values();
                    return result.begin();
                });
    }
};

namespace morpheus::meta::concepts
{

class UnscannableType;

TEST_CASE("Meta concept scannable_with verifies a given type customises conf::scan::scanner", "[morpheus.meta.concepts.scannable_with]")
{
    STATIC_REQUIRE(!detail::ScannableWith<UnscannableType, conf::scan::basic_scan_context<morpheus::conf::ranges::subrange<char*, char*>, char>>);
    STATIC_REQUIRE(detail::ScannableWith<ScannableType, conf::scan::basic_scan_context<morpheus::conf::ranges::subrange<char*, char*>, char>>);
}

TEST_CASE("Meta concept scannable_with verifies a given type customises conf::scan::scanner", "[morpheus.meta.concepts.scannable]")
{
    STATIC_REQUIRE(!Scannable<UnscannableType, char>);
    STATIC_REQUIRE(Scannable<ScannableType, char>);
}

} // namespace morpheus::meta::concepts
