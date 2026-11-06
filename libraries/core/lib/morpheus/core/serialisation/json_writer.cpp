#include "morpheus/core/serialisation/json_writer.hpp"

#include <libassert/assert.hpp>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include <rapidjson/rapidjson.h>

#include <algorithm>

namespace morpheus::serialisation
{

JsonWriter::JsonWriter(std::ostream& stream)
    : mStream(stream)
    , mJsonWriter(mStream)
{}

void JsonWriter::beginComposite()
{
    ASSERT(mJsonWriter.StartObject());
}

void JsonWriter::endComposite()
{
    ASSERT(mJsonWriter.EndObject());
}

void JsonWriter::beginValue(std::string_view const key)
{
    DEBUG_ASSERT(!key.empty());
    ASSERT(mJsonWriter.Key(key.data(), static_cast<rapidjson::SizeType>(key.size())));
}

void JsonWriter::endValue() {}

void JsonWriter::beginSequence(std::optional<std::size_t>)
{
    ASSERT(mJsonWriter.StartArray());
}

void JsonWriter::endSequence()
{
    ASSERT(mJsonWriter.EndArray());
}

void JsonWriter::beginNullable(bool const null)
{
    if (null)
        ASSERT(mJsonWriter.Null());
}

void JsonWriter::endNullable() {}

void JsonWriter::write(bool const value)
{
    ASSERT(mJsonWriter.Bool(value));
}

void JsonWriter::write(std::byte const value)
{
    write(static_cast<std::uint8_t>(value));
}

void JsonWriter::write(std::uint8_t const value)
{
    ASSERT(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int8_t const value)
{
    ASSERT(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint16_t const value)
{
    ASSERT(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int16_t const value)
{
    ASSERT(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint32_t const value)
{
    ASSERT(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int32_t const value)
{
    ASSERT(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint64_t const value)
{
    ASSERT(mJsonWriter.Uint64(value));
}

void JsonWriter::write(std::int64_t const value)
{
    ASSERT(mJsonWriter.Int64(value));
}

void JsonWriter::write(float const value)
{
    ASSERT(mJsonWriter.Double(value));
}

void JsonWriter::write(double const value)
{
    ASSERT(mJsonWriter.Double(value));
}

void JsonWriter::write(std::string_view const value)
{
    DEBUG_ASSERT(!value.empty());
    ASSERT(mJsonWriter.String(value.data(), static_cast<rapidjson::SizeType>(value.size())));
}

void JsonWriter::write(std::span<std::byte const> const value)
{
    using namespace boost::archive::iterators;
    using base64_enc = base64_from_binary<transform_width<unsigned char const*, 6, 8>>;

    auto const* const data = reinterpret_cast<unsigned char const*>(value.data());
    std::string encoded(base64_enc(data), base64_enc(data + value.size()));

    // Add RFC-compliant Base64 padding if the input size is not a multiple of 3.
    encoded.append((3 - value.size() % 3) % 3, '=');

    write(std::string_view(encoded));
}

} // namespace morpheus::serialisation
