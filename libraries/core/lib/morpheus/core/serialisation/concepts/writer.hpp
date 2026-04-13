#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

/// \concept Writer
///     Constraints for a type capable of writing the fundamental serialisable types.
template <typename T>
concept Writer = requires(T t) {
    { t.isTextual() } -> std::same_as<bool>;

    { t.beginSequence(std::optional<std::size_t>{}) } -> std::same_as<void>;
    { t.endSequence() } -> std::same_as<void>;
    { t.beginComposite() } -> std::same_as<void>;
    { t.endComposite() } -> std::same_as<void>;
    { t.beginValue(std::string_view{}) } -> std::same_as<void>;
    { t.endValue() } -> std::same_as<void>;
    { t.beginNullable(bool{}) } -> std::same_as<void>;
    { t.endNullable() } -> std::same_as<void>;

    { t.write(bool{}) } -> std::same_as<void>;
    { t.write(std::uint8_t{}) } -> std::same_as<void>;
    { t.write(std::int8_t{}) } -> std::same_as<void>;
    { t.write(std::uint16_t{}) } -> std::same_as<void>;
    { t.write(std::int16_t{}) } -> std::same_as<void>;
    { t.write(std::uint32_t{}) } -> std::same_as<void>;
    { t.write(std::int32_t{}) } -> std::same_as<void>;
    { t.write(std::uint64_t{}) } -> std::same_as<void>;
    { t.write(std::int64_t{}) } -> std::same_as<void>;
    { t.write(float{}) } -> std::same_as<void>;
    { t.write(double{}) } -> std::same_as<void>;
    { t.write(std::string_view{}) } -> std::same_as<void>;
    { t.write(std::span<std::byte>{}) } -> std::same_as<void>;
};

} // namespace morpheus::serialisation::concepts
