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

TEST_CASE("Support for incomplete types", "[morpheus.memory.polymorphic_value.class]")
{
    class Incomplete;
    polymorphic_value<Incomplete> p;

    REQUIRE_FALSE(bool(p));
}

} // morpheus::memory
