#pragma once

#include <cstddef>
#include <cstdint>
#include <istream>
#include <span>
#include <string_view>

namespace morpheus::serialisation
{

class JsonReader
{
public:
    static constexpr bool canBeTextual() { return true; }
    static constexpr bool isTextual() { return true; }

    explicit JsonReader(std::istream& stream) noexcept : mStream(stream) {}

    void beginComposite() {}
    void endComposite() {}


private:
    std::istream& mStream;
};


}