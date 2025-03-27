#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/base/verify.hpp"
#include "morpheus/core/serialisation/json_writer.hpp"

#include <rapidjson/rapidjson.h> 

namespace morpheus::serialisation
{

JsonWriter::JsonWriter(std::ostream& stream)
:   mStream(stream)
,   mJsonWriter(mStream)
{
//    mJsonWriter.SetMaxDecimalPlaces(6);
}

void JsonWriter::beginComposite()
{
    MORPHEUS_VERIFY(mJsonWriter.StartObject());
}

void JsonWriter::endComposite()
{
    MORPHEUS_VERIFY(mJsonWriter.EndObject());
}

void JsonWriter::beginValue(std::string_view const key)
{
    MORPHEUS_ASSERT(!key.empty());
    MORPHEUS_VERIFY(mJsonWriter.Key(key.data(), static_cast<rapidjson::SizeType>(key.size())));
}

void JsonWriter::endValue()
{
}

void JsonWriter::beginSequence(std::optional<std::size_t>)
{
    MORPHEUS_VERIFY(mJsonWriter.StartArray());
}

void JsonWriter::endSequence()
{
    MORPHEUS_VERIFY(mJsonWriter.EndArray());
}

void JsonWriter::beginNullable(bool const null)
{
    if (null)
       MORPHEUS_VERIFY(mJsonWriter.Null());
}

void JsonWriter::endNullable()
{

}

void JsonWriter::write(bool const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Bool(value));
}

void JsonWriter::write(std::uint8_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int8_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint16_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int16_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint32_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Uint(value));
}

void JsonWriter::write(std::int32_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Int(value));
}

void JsonWriter::write(std::uint64_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Uint64(value));
}

void JsonWriter::write(std::int64_t const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Int64(value));
}

void JsonWriter::write(float const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Double(value));
}

void JsonWriter::write(double const value)
{
    MORPHEUS_VERIFY(mJsonWriter.Double(value));
}

void JsonWriter::write(std::string_view const value)
{
    MORPHEUS_ASSERT(!value.empty());
    MORPHEUS_VERIFY(mJsonWriter.String(value.data(), static_cast<rapidjson::SizeType>(value.size())));
}

void JsonWriter::write(std::span<std::byte const> const) {} // LCOV_EXCL_LINE
}
