#pragma once

#include "morpheus/core/base/cold.hpp"
#include "morpheus/core/conformance/format.hpp"

#include <stdexcept>
#include <string_view>

namespace morpheus::serialisation
{

/// \class BinaryException
///     Exception type to be thrown for errors when parsing binary.
class BinaryException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/// \class JsonException
///     Exception type to be thrown for errors when parsing JSON.
class JsonException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/// \class YamlException
///     Exception type to be thrown for errors when parsing YAML.
class YamlException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/// Throws a std::runtime_error derived binary exception with the attached message.
MORPHEUSCORE_EXPORT [[noreturn]] MORPHEUS_FUNCTION_COLD void throwBinaryException(std::string_view message);

/// Throws a std::runtime_error derived Json exception with the attached message.
MORPHEUSCORE_EXPORT [[noreturn]] MORPHEUS_FUNCTION_COLD void throwJsonException(std::string_view message);

/// Throws a std::runtime_error derived Yaml exception with the attached message.
MORPHEUSCORE_EXPORT [[noreturn]] MORPHEUS_FUNCTION_COLD void throwYamlException(std::string_view message);

} // namespace morpheus::serialisation
