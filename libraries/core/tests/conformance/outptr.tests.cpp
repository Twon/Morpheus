#include "morpheus/core/conformance/outptr.hpp"

#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <cstdlib>
#include <cstring>

// Dummy C-style API
extern "C" {
    struct CObject {
        int value;
    };

    // Allocate a new object
    void create_object(CObject** obj) {
        *obj = static_cast<CObject*>(std::malloc(sizeof(CObject)));
        (*obj)->value = 42;
    }

    // Modify an existing object, reallocating if necessary
    void update_object(CObject** obj, int new_value) {
        if (!*obj) {
            *obj = static_cast<CObject*>(std::malloc(sizeof(CObject)));
        }
        (*obj)->value = new_value;
    }

    // Free an object
    void destroy_object(CObject* obj) {
        std::free(obj);
    }
}



namespace morpheus
{

TEST_CASE("std::out_ptr works for initial ownership acquisition", "[morpheus.conformance.outptr]") {
    std::unique_ptr<CObject, decltype(&destroy_object)> ptr(nullptr, &destroy_object);

    // Acquire ownership from a raw C API using out_ptr
    create_object(conf::ptr::out_ptr(ptr));

    REQUIRE(ptr != nullptr);
    REQUIRE(ptr->value == 42);
}

TEST_CASE("std::inout_ptr works for modifying existing allocation", "[morpheus.conformance.inoutptr]") {
    std::unique_ptr<CObject, decltype(&destroy_object)> ptr(nullptr, &destroy_object);

    // First allocate
    create_object(conf::ptr::out_ptr(ptr));
    REQUIRE(ptr->value == 42);

    // Now update the existing object with a new value using inout_ptr
    update_object(conf::ptr::inout_ptr(ptr), 99);
    REQUIRE(ptr != nullptr);
    REQUIRE(ptr->value == 99);
}

} // namespace morpheus
