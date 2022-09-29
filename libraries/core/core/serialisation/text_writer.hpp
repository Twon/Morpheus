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

    explicit TextWriter(std::ostream& stream) noexcept : mStream(stream) {}

    void write(bool value) {}
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
    void write(std::string_view const value) {}
    void write(std::span<std::bytes> const value) {}

private:
    std::ostream& mStream;
};

}