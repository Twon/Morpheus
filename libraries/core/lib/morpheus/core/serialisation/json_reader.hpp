#pragma once

#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/base/export.hpp"
#include "morpheus/core/functional/overload.hpp"
#include "morpheus/core/serialisation/concepts/reader_archetype.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"

#include <boost/numeric/conversion/cast.hpp>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/reader.h>

#include <magic_enum/magic_enum.hpp>

#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

namespace morpheus::serialisation
{

/// \class JsonReader
///     Read in objects from an underlying json representation.
class MORPHEUSCORE_EXPORT JsonReader
{
    enum class FundamentalType : std::uint32_t
    {
        Boolean,
        Int64,
        Uint64,
        Float,
        Double,
        String
    };

public:
    using OwnedStream = std::unique_ptr<std::istream>;

    static constexpr bool canBeTextual() { return true; }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::isTextual()
    static constexpr bool isTextual() { return true; }

    /// Json reader take in a stream of json to extract data members from.
    /// \param[in] stream Stream used to read in the json source.  This must outlive the reader as its held by reference.
    /// \param[in] validate If true, the json will be validated against the schema.  If false, no validation is performed.
    explicit JsonReader(OwnedStream stream, bool validate = true);

    explicit JsonReader(JsonReader const& rhs) = delete;
    JsonReader& operator=(JsonReader const& rhs) = delete;

    explicit JsonReader(JsonReader&& rhs) noexcept = delete;
    JsonReader& operator=(JsonReader&& rhs) noexcept = delete;

    /// Destructor for the JsonReader.
    ~JsonReader();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::beginComposite()
    void beginComposite();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::endComposite()
    void endComposite();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::beginValue()
    void beginValue(std::string_view const key);

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::endValue()
    void endValue();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::beginSequence()
    std::optional<std::size_t> beginSequence();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::endSequence()
    void endSequence();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::beginNullable()
    bool beginNullable();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchetype::endNullable()
    void endNullable();

    // clang-format off
    /// Read a boolean from the serialisation.
    template <typename T>
    requires std::is_same_v<T, bool>
    T read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT(next->index() == 0);
        return std::get<T>(*next);
    }

    /// Reads a integral type from the serialisation.
    template <std::integral Integer>
    requires(not std::is_same_v<bool, Integer>)
    Integer read()
    {
        auto const [event, next] = getNext();
        return std::visit(functional::Overload{
            [](std::integral auto const value) { return boost::numeric_cast<Integer>(value); },
            [](auto const) -> Integer { throwJsonException("Unable to convert to integral representation"); }
        }, *next);
    }

    /// Reads a float or double type from the serialisation.
    template <std::floating_point Float>
    Float read()
    {
        auto const [event, next] = getNext();
        return std::visit(functional::Overload {
            [](std::integral auto const value) { return boost::numeric_cast<Float>(value); },
            [](std::floating_point auto const value)
            {
                if (std::isinf(value)) [[unlikely]]
                {
                    if (value > 0)
                        return std::numeric_limits<Float>::infinity();
                    else
                        return -std::numeric_limits<Float>::infinity();
                }
                return boost::numeric_cast<Float>(value);
            },
            [](auto const) -> Float { throwJsonException("Unable to convert to floating point representation"); }
        }, *next);
    }

    /// Reads a string type from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::string>
    T read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT(next->index() == magic_enum::enum_integer(FundamentalType::String));
        return std::get<T>(*next);
    }

    /// Read a blob of binary from the serialisation.
    template <typename T>
    requires std::is_same_v<T, std::vector<std::byte>>
    T read()
    {
        return {};
    }
    // clang-format on
private:
    enum class Event : std::uint32_t
    {
        BeginComposite,
        EndComposite,
        BeginValue,
        Value,
        EndValue,
        BeginSequence,
        EndSequence,
    };

    friend struct JsonExtracter;
    using FundamentalValue = std::variant<bool, std::int64_t, std::uint64_t, float, double, std::string>;
    using PossibleValue = std::optional<FundamentalValue>;
    using EventValue = std::tuple<Event, PossibleValue>;

    [[nodiscard]] EventValue getNext();

    OwnedStream mSourceStream; /// Owned input stream containing the Json source.
    rapidjson::IStreamWrapper mStream;
    rapidjson::Reader mJsonReader;
    std::unique_ptr<struct JsonExtracter> mExtractor;
    bool mValidate = true;
};

} // namespace morpheus::serialisation
