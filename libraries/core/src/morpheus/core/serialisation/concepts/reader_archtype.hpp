#pragma once

#include "morpheus/core/serialisation/read_serialiser_decl.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation::concepts
{

struct ReaderArchtype
{
    consteval bool isTextual() noexcept;

    consteval void beginComposite();
    consteval void endComposite();
    consteval void beginValue(std::string_view const key);
    consteval void endValue();
    consteval std::optional<std::size_t> beginSequence();
    consteval void endSequence();
    consteval bool beginNullable();
    consteval void endNullable();

    template <typename T> requires std::is_arithmetic_v<T>
    T read();

    template <typename T> requires std::is_same_v<T, std::string>
    consteval T read();

//    template <typename T> requires std::is_same_v<T, std::vector<std::bytes>>
//    constinit T read();
};

using ReadSerialiserArchtype = serialisation::ReadSerialiser<ReaderArchtype>;

} // morpheus::serialisation::concepts