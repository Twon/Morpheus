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

/*
    { t.isTextual() } -> std::same_as<bool>;

    { t.template read<bool>() } -> std::same_as<bool>;
    { t.template read<std::uint8_t>() } -> std::same_as<std::uint8_t>;
    { t.template read<std::int8_t>() } -> std::same_as<std::int8_t>;
    { t.template read<std::uint16_t>() } -> std::same_as<std::uint16_t>;
    { t.template read<std::int16_t>() } -> std::same_as<std::int16_t>;
    { t.template read<std::uint32_t>() } -> std::same_as<std::uint32_t>;
    { t.template read<std::int32_t>()) } -> std::same_as<std::int32_t>;
    { t.template read<std::uint64_t>() } -> std::same_as<std::uint64_t>;
    { t.template read<std::int64_t>() } -> std::same_as<std::int64_t>;
    { t.template read<float>() } -> std::same_as<float>;
    { t.template read<double>() } -> std::same_as<double>;

    template<typename T>
    T read() {};
*/

/*
    void write(bool const value) {}
    void write(std::uint8_t const value) {}
    void write(std::int8_t const value) {}
    void write(std::uint16_t const value) {}
    void write(std::int16_t const value) {}
    void write(std::uint32_t const value) {}
    void write(std::int32_t const value) {}
    void write(std::uint64_t const value) {}
    void write(std::int64_t const value) {}
    void write(float const value) {}
    void write(double const value) {}
    void write(std::string_view const value) {}
    void write(std::span<std::byte> const value) {}
*/
private:
    std::istream& mStream;
};


}