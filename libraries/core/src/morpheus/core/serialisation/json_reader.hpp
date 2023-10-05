#pragma once

#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/base/cold.hpp"
#include "morpheus/core/base/scoped_action.hpp"
#include "morpheus/core/concurrency/generator.hpp"
#include "morpheus/core/functional/overload.hpp"
#include "morpheus/core/memory/polymorphic_value.hpp"
#include "morpheus/core/serialisation/exceptions.hpp"
#include "morpheus/core/serialisation/concepts/reader_archtype.hpp"
#include "morpheus/core/serialisation/read_serialiser_decl.hpp"

#include <boost/numeric/conversion/cast.hpp>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/reader.h>

#include <magic_enum.hpp>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
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
    using OwnedStream = memory::polymorphic_value<std::istream>;



    static constexpr bool canBeTextual() { return true; }

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::isTextual()
    static constexpr bool isTextual() { return true; }

    /// Json reader take in a stream of json to extract data members from.
    /// \param[in] stream Stream used to read in the json source.  This must outlive the reader as its held by referece.
    explicit JsonReader(OwnedStream stream, bool validate = true);
    explicit JsonReader(JsonReader const& rhs);
    ~JsonReader();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginComposite()
    void beginComposite();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endComposite()
    void endComposite();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginValue()
    void beginValue(std::string_view const key);

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endValue()
    void endValue();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginSequence()
    std::optional<std::size_t> beginSequence();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endSequence()
    void endSequence();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::beginNullable()
    bool beginNullable();

    /// \copydoc morpheus::serialisation::concepts::ReaderArchtype::endNullable()
    void endNullable();

    template <typename T>
        requires requires(concepts::ReaderArchtype& r) {
            {
                r.template read<T>()
            } -> std::same_as<T>;
        }
    concurrency::Generator<T> readSequence()
    {
        for (;;) {
            auto const [event, next] = getNext();
            repeatCurrent();

            if (event == Event::EndSequence) {
                co_return;
            }

            MORPHEUS_ASSERT(event == Event::Value);
            co_yield read<T>();
        }
    }

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
    template <std::integral Interger>
    requires(not std::is_same_v<bool, Interger>)
    Interger read()
    {
        auto const [event, next] = getNext();
        return std::visit(functional::Overload{
            [](std::integral auto const value) { return boost::numeric_cast<Interger>(value); },
            [](auto const value) -> Interger { throwJsonException("Unable to convert to integral representation"); }
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
            [](auto const value) -> Float { throwJsonException("Unable to convert to floating point representation"); }
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

    friend class JsonExtracter;
    using FundamentalValue = std::variant<bool, std::int64_t, std::uint64_t, float, double, std::string>;
    using PossibleValue = std::optional<FundamentalValue>;
    using EventValue = std::tuple<Event, PossibleValue>;

    [[nodiscard]] EventValue getNext();
    void repeatCurrent();

    memory::polymorphic_value<std::istream> mSourceStream; /// Owned input stream containing the Json source.
    rapidjson::IStreamWrapper mStream;
    rapidjson::Reader mJsonReader;
    std::unique_ptr<class JsonExtracter> mExtractor;
    bool mValidate = true;
    bool mRepeat = false;
};

} // namespace morpheus::serialisation