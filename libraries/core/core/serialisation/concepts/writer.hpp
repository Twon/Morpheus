#pragma once

#include <cstdint>
#include <type_traits>

namespace morpheus::serialisation
{

template <typename T>
concept Writer = requires(T t)
{
    { t.isTextual() } -> std::same_as<bool>;

    { t.write(true) };
    { t.write(std::uint8_t(0)) };
    { t.write(std::int8_t(0)) };
    { t.write(std::uint16_t(0)) };
    { t.write(std::int16_t(0)) };
    { t.write(std::uint32_t(0)) };
    { t.write(std::int32_t(0)) };
    { t.write(std::uint64_t(0)) };
    { t.write(std::int64_t(0)) };
    { t.write(0.0f) };
    { t.write(0.0) };
};

}