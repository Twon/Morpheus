#pragma once

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <span>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

template <typename T>
concept Reader = requires(T t)
{
    { t.isTextual() } -> std::same_as<bool>;

    { t.beginComposite() } -> std::same_as<void>;
    { t.endComposite() } -> std::same_as<void>;
    { t.beginValue(std::string_view{}) } -> std::same_as<void>;
    { t.endValue() } -> std::same_as<void>;

    { t.template read<bool>() } -> std::same_as<bool>;
    { t.template read<std::uint8_t>() } -> std::same_as<std::uint8_t>;
    { t.template read<std::int8_t>() } -> std::same_as<std::int8_t>;
    { t.template read<std::uint16_t>() } -> std::same_as<std::uint16_t>;
    { t.template read<std::int16_t>() } -> std::same_as<std::int16_t>;
    { t.template read<std::uint32_t>() } -> std::same_as<std::uint32_t>;
    { t.template read<std::int32_t>() } -> std::same_as<std::int32_t>;
    { t.template read<std::uint64_t>() } -> std::same_as<std::uint64_t>;
    { t.template read<std::int64_t>() } -> std::same_as<std::int64_t>;
    { t.template read<float>() } -> std::same_as<float>;
    { t.template read<double>() } -> std::same_as<double>;
};

} // morpheus::serialisation::concepts