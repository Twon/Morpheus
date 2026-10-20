#include "morpheus/core/conformance/value_types.hpp"

#include <catch2/catch_test_macros.hpp>

namespace morpheus
{

namespace
{

class Base
{
public:
    Base() = default;
    Base(Base const&) = default;
    Base& operator=(Base const&) = default;
    Base(Base&&) = default;
    Base& operator=(Base&&) = default;

    virtual ~Base() = default;
    [[nodiscard]] virtual int getValue() const = 0;
};

class Derived : public Base
{
    int value;

public:
    explicit Derived(int value_)
        : value(value_)
    {}
    [[nodiscard]] int getValue() const noexcept override { return value; }
};

} // namespace

TEST_CASE("Ensure value types are supported and working", "[morpheus.conformance.value_types.indirect]")
{
    using conf::vt::indirect;

    indirect value(42);
    REQUIRE(*value == 42);
}

TEST_CASE("Ensure value types are supported and working", "[morpheus.conformance.value_types.polymorphic]")
{
    using conf::vt::polymorphic;

    polymorphic<Base> value(std::in_place_type<Derived>, 64);
    REQUIRE(value->getValue() == 64);
}

} // namespace morpheus
