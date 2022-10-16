#pragma once

#include "core/base/assert.hpp"
#include "core/functional/overload.hpp"

#include <boost/numeric/conversion/cast.hpp>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/reader.h>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <string>
#include <tuple>
#include <variant>

namespace morpheus::serialisation
{

/// \class JsonReader
/// 
class MORPHEUSCORE_EXPORT JsonReader
{
public:
    /// \class Exception
    /// 
    class Exception : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

    static constexpr bool canBeTextual() { return true; }
    static constexpr bool isTextual() { return true; }

    explicit JsonReader(std::istream& stream);
    ~JsonReader();

    void beginComposite();
    void endComposite();
    void beginValue(std::string_view const key);
    void endValue();
    void beginSequence(std::optional<std::size_t> = std::nullopt);
    void endSequence();

    template<typename T> requires std::is_same_v<T, bool>
    T read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT(next->index() == 0);
        return std::get<T>(*next);
    }

    template<std::integral Interger> requires (not std::is_same_v<bool, Interger>)
    Interger read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT((next->index() == 1) or (next->index() == 2));
        return std::visit(functional::Overload{
            [](std::integral auto const value) { return boost::numeric_cast<Interger>(value); },
            [](auto const value) -> Interger { throw Exception("Unable to convert to integral point representation"); }
        }, *next);
    }

    template<std::floating_point Float>
    Float read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT((next->index() == 1) or (next->index() == 2) or (next->index() == 3) or (next->index() == 4));
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
            [](auto const value) -> Float { throw Exception("Unable to convert to floating point representation"); }
        }, *next);
    }

    template<typename T> requires std::is_same_v<T, std::string>
    T read()
    {
        auto const [event, next] = getNext();
        MORPHEUS_ASSERT(next->index() == 5);
        return std::get<T>(*next);
    }
/*

    { t.template read<bool>() } -> std::same_as<bool>;
    { t.template read<std::uint8_t>() } -> std::same_as<std::uint8_t>;
    { t.template read<std::int8_t>() } -> std::same_as<std::int8_t>;
    { t.template read<std::uint16_t>() } -> std::same_as<std::uint16_t>;
    { t.template read<std::int16_t>() } -> std::same_as<std::int16_t>;
    { t.template read<std::uint32_t>() } -> std::same_as<std::uint32_t>;
    { t.template read<std::int32_t>()) } -> std::same_as<std::int32_t>;
    { t.template read<std::uint64_t>() } -> std::same_as<std::uint64_t>;
    { t.template read<std::int64_t>() } -> std::same_as<std::int64_t>;
    { t.template read<float>() } -> std::same_as<float>;
    { t.template read<double>() } -> std::same_as<double>;

*/

/*
    void write(std::string_view const value) {}
    void write(std::span<std::byte> const value) {}
*/

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
    using FundamentalType = std::variant<bool, std::int64_t, std::uint64_t, float, double, std::string>;
    using PossibleValue = std::optional<FundamentalType>;
    using EventValue = std::tuple<Event, PossibleValue>;

    [[nodiscard]] EventValue getNext();

    rapidjson::IStreamWrapper mStream;
    rapidjson::Reader mJsonReader;
    std::unique_ptr<class JsonExtracter> mExtractor;
};


}