#include <morpheus/core/meta/invocable_traits.hpp>

#include <catch2/catch_all.hpp>

namespace morpheus::meta
{

auto exceptInvocableFunction() noexcept(false) {}
auto noexceptInvocableFunction() noexcept {}

TEST_CASE("Meta is nothrow invocable the compile time detection of noexcept invocable types", "[morpheus.meta.is_nothrow_invocable]")
{
    auto const exceptInvocable = []() noexcept(false) {};
    auto const noexceptInvocable = []() noexcept {};
    STATIC_REQUIRE(!meta::IsNothrowInvocable<decltype(exceptInvocable)>);
    STATIC_REQUIRE(meta::IsNothrowInvocable<decltype(noexceptInvocable)>);
    STATIC_REQUIRE(!meta::IsNothrowInvocable<decltype(exceptInvocableFunction)>);
    STATIC_REQUIRE(meta::IsNothrowInvocable<decltype(noexceptInvocableFunction)>);
}

} // namespace morpheus::meta
