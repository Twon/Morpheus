#pragma once

#include "morpheus/core/serialisation/read_serialiser_decl.hpp"

#include <toml++/toml.hpp>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>

namespace morpheus::serialisation
{

/// \class TomlReader
///     Implements the concept Reader for a streaming TOML reader which extracts items one by one from the input stream.
class TomlReader
{
public:
    TomlReader(std::istream& stream);

    /// Query if the underlying serialisation format is text based.
    static constexpr bool isTextual() noexcept { return true; }

    /// Begin reading a composite type.
    void beginComposite();

    /// End reading a composite type.
    void endComposite();

    /// Begin reading a key to value type mapping.
    void beginValue(std::string_view const key);

    /// End reading a key to value type mapping.
    void endValue();

    /// Begin reading a sequence of values.
    /// \return Optionally provide the size of the sequence to be written.
    std::optional<std::size_t> beginSequence();

    /// End reading a sequence of values.
    void endSequence();

    /// Begin reading a nullable value.
    /// \return If the nullable type should read a value from the serialisation.
    bool beginNullable();

    /// End reading a nullable value.
    void endNullable();

    /// Read any arithmetic type from the serialisation.
    template <typename T>
    requires std::is_arithmetic_v<T> or std::same_as<T, std::byte>
    T read()
    {
        return T{};
    }

    /// Read a string from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::string>
    T read()
    {
        return T{};
    }

    /// Read a blob of binary from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::vector<std::byte>>
    T read()
    {
        return T{};
    }

    /// Read a sequence of values from the serialisation.
    template <typename T, typename Fn>
    concurrency::Generator<T> readElements(Fn readOne, std::optional<std::size_t> size)
    {
        return [readOne = std::move(readOne), size]() -> concurrency::Generator<T>
        {
            if (size)
            {
                for (std::size_t i = 0; i < *size; ++i)
                    co_yield readOne();
            }
            else
            {
                // while (!isAtEndSequence())
                //     co_yield readOne();
            }
        }();
    }

private:
    std::istream& mStream;
    toml::table mTable;
};

} // namespace morpheus::serialisation
