#include "morpheus/core/conformance/scan.hpp"
#include "morpheus/core/meta/concepts/scannable.hpp"

#include <catch2/catch_all.hpp>

#include <tuple>

struct ScannableType
{
    int first = 0;
    double second = 0.0;
};

template <>
struct morpheus::scan_ns::scanner<ScannableType> : morpheus::scan_ns::scanner<std::string>
{
    template <typename Context>
    auto scan(ScannableType& val, Context& ctx) const -> morpheus::scan_ns::scan_expected<typename Context::iterator>
    {
        return morpheus::scan_ns::scan<int, int>(ctx.range(), "[{}, {}]")
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

TEST_CASE("Meta concept scannable_with verifies a given type customises scan_ns::scanner", "[morpheus.meta.concepts.scannable_with]")
{
    STATIC_REQUIRE(!detail::ScannableWith<UnscannableType, scan_ns::basic_scan_context<char>>);
    STATIC_REQUIRE(detail::ScannableWith<ScannableType, scan_ns::basic_scan_context<char>>);
}

TEST_CASE("Meta concept scannable_with verifies a given type customises scan_ns::scanner", "[morpheus.meta.concepts.scannable]")
{
    STATIC_REQUIRE(!Scannable<UnscannableType, char>);
    STATIC_REQUIRE(Scannable<ScannableType, char>);
}

} // namespace morpheus::meta::concepts
