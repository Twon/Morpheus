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

void TomlReader::beginValue(std::string_view const key)
{
    if (mCurrentKey)
        mKeyStack.push_back(*mCurrentKey);

    mCurrentKey = std::string(key);
}

void TomlReader::endValue()
{
    if (!mKeyStack.empty())
    {
        mCurrentKey = mKeyStack.back();
        mKeyStack.pop_back();
    }
    else
    {
        mCurrentKey.reset();
    }
}

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
