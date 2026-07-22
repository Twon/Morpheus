#include "morpheus/core/serialisation/toml_writer.hpp"

namespace morpheus::serialisation
{

TomlWriter::TomlWriter(std::ostream& stream)
    : mStream(stream)
//,   mTable(toml::parse(mStream))
{}

void TomlWriter::beginComposite() {}

void TomlWriter::endComposite() {}

void TomlWriter::beginValue(std::string_view const key) {}

void TomlWriter::endValue() {}

void TomlWriter::beginSequence(std::optional<std::size_t> size) {}

void TomlWriter::endSequence() {}

void TomlWriter::beginNullable(bool const null) {}

void TomlWriter::endNullable() {}

void TomlWriter::write(bool const value) {}

void TomlWriter::write(std::byte const value) {}

void TomlWriter::write(std::uint8_t const value) {}

void TomlWriter::write(std::int8_t const value) {}

void TomlWriter::write(std::uint16_t const value) {}

void TomlWriter::write(std::int16_t const value) {}

void TomlWriter::write(std::uint32_t const value) {}

void TomlWriter::write(std::int32_t const value) {}

void TomlWriter::write(std::uint64_t const value) {}

void TomlWriter::write(std::int64_t const value) {}

void TomlWriter::write(float const value) {}

void TomlWriter::write(double const value) {}

void TomlWriter::write(std::string_view const value) {}

void TomlWriter::write(std::span<std::byte const> const value) {}

} // namespace morpheus::serialisation
