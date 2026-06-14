#include "morpheus/core/serialisation/toml_reader.hpp"

#include <istream>

namespace morpheus::serialisation
{

TomlReader::TomlReader(std::istream& stream)
    : mStream(stream)
    , mTable(toml::parse(mStream))
{}

void TomlReader::beginComposite() {}

void TomlReader::endComposite() {}

void TomlReader::beginValue(std::string_view const key) {}

void TomlReader::endValue() {}

std::optional<std::size_t> TomlReader::beginSequence()
{
    return std::nullopt;
}

void TomlReader::endSequence() {}

bool TomlReader::beginNullable()
{
    return false;
}

void TomlReader::endNullable() {}

} // namespace morpheus::serialisation
