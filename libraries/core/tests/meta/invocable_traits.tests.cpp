#include <morpheus/core/meta/invocable_traits.hpp>

#include <catch2/catch_test_macros.hpp>

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

struct TestForConstness
{
    void operator()() const {}
    void operator()(int, bool) const {}
};

struct TestForMutable
{
    void operator()() {}
    void operator()(int, bool) {}
};

TEST_CASE("Meta is const invocable the compile time detection of const invocable types", "[morpheus.meta.is_const_invocable]")
{
    auto const constInvocable = []() {};
    auto const mutableInvocable = []() mutable {};
    STATIC_REQUIRE(meta::IsConstInvocable<TestForConstness>);
    STATIC_REQUIRE(meta::IsConstInvocable<TestForConstness, int, bool>);
    STATIC_REQUIRE(!meta::IsConstInvocable<TestForMutable>);
    STATIC_REQUIRE(!meta::IsConstInvocable<TestForMutable, int, bool>);
    STATIC_REQUIRE(meta::IsConstInvocable<decltype(constInvocable)>);
    STATIC_REQUIRE(meta::IsConstInvocable<decltype(mutableInvocable)>);
}

} // namespace morpheus::meta
