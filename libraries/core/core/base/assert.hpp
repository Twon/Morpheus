#pragma once

#include <string_view>

namespace morpheus 
{

    void assertHandler(std::string_view const expr, std::string_view const file, std::uint32_t line);

#define MORPHEUS_ASSERT()

}