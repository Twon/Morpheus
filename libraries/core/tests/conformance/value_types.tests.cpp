#include "morpheus/core/conformance/value_types.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus
{

class Base
{
public:
    virtual ~Base() {}
    virtual int getValue() const = 0;
};

class Derived : public Base
{
    int value;

public:
    Derived(int value_)
        : value(value_)
    {}
    int getValue() const { return value; }
};

TEST_CASE("Ensure value types are supported and working", "[morpheus.conformance.value_types.indirect]")
{
    using namespace conf::vt;

    indirect value(42);
    REQUIRE(*value == 42);
}

TEST_CASE("Ensure value types are supported and working", "[morpheus.conformance.value_types.polymorphic]")
{
    using namespace conf::vt;

    polymorphic<Base> value(std::in_place_type<Derived>, 64);
    REQUIRE(value->getValue() == 64);
}

} // namespace morpheus
