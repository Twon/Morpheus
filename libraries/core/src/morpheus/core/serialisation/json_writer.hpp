#pragma once

#include "core/base/platform.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <optional>
#include <span>
#include <string_view>

namespace morpheus::serialisation
{

/// \class JsonWriter
///     Implementes the concept \ref Writer for a streaming JSON writer which writes item by item to the output stream.
class MORPHEUSCORE_EXPORT JsonWriter
{
public:
    static constexpr bool canBeTextual() { return true; }
    static constexpr bool isTextual() { return true; }

    explicit JsonWriter(std::ostream& stream);

    void beginComposite();
    void endComposite();
    void beginValue(std::string_view const key);
    void endValue();
    void beginSequence(std::optional<std::size_t> = std::nullopt);
    void endSequence();
    void beginNullable(bool const null);
    void endNullable();

    void write(bool const value);
    void write(std::uint8_t const value);
    void write(std::int8_t const value);
    void write(std::uint16_t const value);
    void write(std::int16_t const value);
    void write(std::uint32_t const value);
    void write(std::int32_t const value);
    void write(std::uint64_t const value);
    void write(std::int64_t const value);
    void write(float const value);
    void write(double const value);
    void write(std::string_view const value);
    void write(std::span<std::byte> const value);

    template <std::size_t N> void write(const char(&str)[N]) { write(std::string_view(str, N-1)); }

private:
    template<typename OutputStream>
    using RapidJsonWriter = rapidjson::Writer<
        OutputStream,
        rapidjson::UTF8<>,
        rapidjson::UTF8<>,
        rapidjson::CrtAllocator,
        (rapidjson::kWriteDefaultFlags | rapidjson::kWriteNanAndInfFlag)
    >;

    rapidjson::OStreamWrapper mStream;
    RapidJsonWriter<rapidjson::OStreamWrapper> mJsonWriter;
};


}