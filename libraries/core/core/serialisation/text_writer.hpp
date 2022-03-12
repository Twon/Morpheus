#pragma once

#include <cstdint>
#include <ostream>

namespace morpheus::serialisation
{

class TextWriter 
{
public:
    static constexpr bool canBeTextual() { return true; }
    static constexpr bool isTextual() { return true; }

    explicit TextWriter(std::ostream& stream) : mStream(stream) {}

    void write(std::uint8_t value) {}
    void write(std::int8_t value) {}
    void write(std::uint16_t value) {}
    void write(std::int16_t value) {}
    void write(std::uint32_t value) {}
    void write(std::int32_t value) {}
    void write(std::uint64_t value) {}
    void write(std::int64_t value) {}
    void write(float value) {}
    void write(double value) {}
private:
    std::ostream& mStream;
};

}