#include "morpheus/core/memory/polymorphic_value.hpp"

#include <catch2/catch_all.hpp>

namespace morpheus::memory
{

namespace
{

struct BaseType
{
    virtual int value() const = 0;
    virtual void set_value(int) = 0;
    virtual ~BaseType() = default;
};

struct DerivedType : BaseType
{
    int value_ = 0;

    DerivedType() { ++object_count; }

    DerivedType(const DerivedType& d)
    {
        value_ = d.value_;
        ++object_count;
    }

    DerivedType(int v)
    : value_(v)
    {
        ++object_count;
    }

    ~DerivedType() { --object_count; }

    int value() const override { return value_; }

    void set_value(int i) override { value_ = i; }

    static size_t object_count;
};

size_t DerivedType::object_count = 0;

} // namespace

TEST_CASE("Support for incomplete types", "[morpheus.memory.polymorphic_value.incomplete]")
{
    class Incomplete;
    polymorphic_value<Incomplete> p;

    REQUIRE_FALSE(bool(p));
}

TEST_CASE("Default constructor", "[morpheus.memory.polymorphic_value.constructor.default]")
{
    GIVEN("A default constructed polymorphic_value to BaseType")
    {
        polymorphic_value<BaseType> cptr;

        THEN("operator bool returns false") { REQUIRE((bool)cptr == false); }
    }

    GIVEN("A default constructed const polymorphic_value to BaseType")
    {
        const polymorphic_value<BaseType> ccptr;

        THEN("operator bool returns false") { REQUIRE((bool)ccptr == false); }
    }
}

// TEST_CASE("Value constructor", "[morpheus.memory.polymorphic_value.constructors]")
// {
//     DerivedType d(7);

//     polymorphic_value<BaseType> i(std::in_place_type<DerivedType>, d);

//     REQUIRE(i->value() == 7);
// }

// TEST_CASE("Value constructor rvalue", "[morpheus.memory.polymorphic_value.constructors]")
// {
//     polymorphic_value<BaseType> i(std::in_place_type<DerivedType>, 7);

//     REQUIRE(i->value() == 7);
// }

// TEST_CASE("Value move-constructor", "[morpheus.memory.polymorphic_value.constructors]")
// {
//     DerivedType d(7);

//     polymorphic_value<BaseType> i(std::in_place_type<DerivedType>, std::move(d));

//     REQUIRE(i->value() == 7);
// }

TEST_CASE("Pointer constructor", "[polymorphic_value.constructors]")
{
    GIVEN("A pointer-constructed polymorphic_value")
    {
        int v = 7;
        polymorphic_value<BaseType> cptr(new DerivedType(v));

        THEN("Operator-> calls the pointee method") { REQUIRE(cptr->value() == v); }

        THEN("operator bool returns true") { REQUIRE((bool)cptr == true); }
    }
    GIVEN("A pointer-constructed const polymorphic_value")
    {
        int v = 7;
        const polymorphic_value<BaseType> ccptr(new DerivedType(v));

        THEN("Operator-> calls the pointee method") { REQUIRE(ccptr->value() == v); }

        THEN("operator bool returns true") { REQUIRE((bool)ccptr == true); }
    }
    GIVEN("Ensure nullptr pointer-constructed const polymorphic_value construct to be default initialised")
    {
        DerivedType* null_derived_ptr = nullptr;
        const polymorphic_value<BaseType> ccptr(null_derived_ptr);

        THEN("operator bool returns true") { REQUIRE((bool)ccptr == false); }
    }
    GIVEN("Ensure polymorphic supports construction from nullptr")
    {
        const polymorphic_value<BaseType> ccptr(nullptr);

        THEN("operator bool returns true") { REQUIRE((bool)ccptr == false); }
    }
}

} // morpheus::memory
