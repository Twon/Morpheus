#include <catch2/catch_all.hpp>

#include <memory>
#include <functional>

namespace morpheus
{

TEST_CASE("Ensure the address sanitizer detects unsafe use after free memory usage", "[quantbox.cmake.asan]")
{
    auto storage = std::make_unique<int>(1);
    std::reference_wrapper<int> dangling(*storage);
    storage.release();
    REQUIRE(!storage);
    dangling.get() = 0; // If asan works this is an error!
}

} // morpheus
