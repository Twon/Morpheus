#include "core/meta/concepts/aggregate.hpp"
#include "core/meta/concepts/aggregate_constructible.hpp"
#include "core/meta/detail/any.hpp"
#include "core/meta/aggregate.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::meta
{

struct SimpleAggregate
{
    int first;
    double second;
    bool third;
};

struct AggregateWithArray
{
    int first[5];
    double second;
};

TEST_CASE("Aggregate allows contraining a type to being an aggregate", "[morpheus.meta.aggregate.fieldsCount]")
{
//    STATIC_REQUIRE(fieldsCount<SimpleAggregate>() == 3);
//    STATIC_REQUIRE(fieldsCount<AggregateWithArray>() == 2);
}

struct TestAggregate
{
    int first;
    int second;
    int third;
};

struct TestNonAggregate : private TestAggregate
{
    TestNonAggregate() = default;
};

TEST_CASE("Aggregate allows contraining a type to being an aggregate", "[morpheus.meta.concept.aggregate]")
{
    STATIC_REQUIRE(concepts::Aggregate<TestAggregate>);
    STATIC_REQUIRE(!concepts::Aggregate<TestNonAggregate>);
}

TEST_CASE("Aggregate constructable allows contraining a type to being an aggregate and constructable from a given set of parameter types", "[morpheus.meta.concept.aggregate_constructable]")
{
#if (__cpp_aggregate_paren_init >= 201902L)
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, int>);
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, int>);
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, int, int>);
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, int, int, int>);
    STATIC_REQUIRE(!concepts::AggregateConstructable<TestAggregate, int, int, int, int>);
    STATIC_REQUIRE(!concepts::AggregateConstructable<TestAggregate, int, int, int, int, int>);
#endif // #if (__cpp_aggregate_paren_init >= 201902L)
}

TEST_CASE("Aggregate constructable with type convertable to any", "[morpheus.meta.concept.aggregate_constructable_to_any]")
{
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, detail::Any>);
#if (__cpp_aggregate_paren_init >= 201902L)
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, detail::Any, detail::Any>);
    STATIC_REQUIRE(concepts::AggregateConstructable<TestAggregate, detail::Any, detail::Any, detail::Any>);
    STATIC_REQUIRE(!concepts::AggregateConstructable<TestAggregate, detail::Any, detail::Any, detail::Any, detail::Any>);
    STATIC_REQUIRE(!concepts::AggregateConstructable<TestAggregate, detail::Any, detail::Any, detail::Any, detail::Any, detail::Any>);
#endif // #if (__cpp_aggregate_paren_init >= 201902L)
}

TEST_CASE("Aggregate constructable from indicies", "[morpheus.meta.concept.aggregate_constructable_from_indicies]")
{
    STATIC_REQUIRE(detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<>>::value);
    STATIC_REQUIRE(detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0>>::value);
#if (__cpp_aggregate_paren_init >= 201902L)
    STATIC_REQUIRE(detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0, 1>>::value);
    STATIC_REQUIRE(detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0, 1, 2>>::value);
    STATIC_REQUIRE(!detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0, 1, 2, 3>>::value);
    STATIC_REQUIRE(!detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0, 1, 2, 3, 4>>::value);
    STATIC_REQUIRE(!detail::AggregateConstructibleFromIndicies<TestAggregate, std::index_sequence<0, 1, 2, 3, 4, 5>>::value);
#endif // #if (__cpp_aggregate_paren_init >= 201902L)
}

TEST_CASE("Aggregate constructable with N arguments", "[morpheus.meta.concept.aggregate_constructable_with_n_args]")
{
    STATIC_REQUIRE(concepts::AggregateConstructableWithNArgs<TestAggregate, 0>);
    STATIC_REQUIRE(concepts::AggregateConstructableWithNArgs<TestAggregate, 1>);
#if (__cpp_aggregate_paren_init >= 201902L)
    STATIC_REQUIRE(concepts::AggregateConstructableWithNArgs<TestAggregate, 2>);
    STATIC_REQUIRE(concepts::AggregateConstructableWithNArgs<TestAggregate, 3>);
    STATIC_REQUIRE(!concepts::AggregateConstructableWithNArgs<TestAggregate, 4>);
    STATIC_REQUIRE(!concepts::AggregateConstructableWithNArgs<TestAggregate, 5>);
#endif // #if (__cpp_aggregate_paren_init >= 201902L)
}

} // namespace morpheus::meta
