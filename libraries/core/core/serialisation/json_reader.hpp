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
#include <variant>

namespace morpheus::serialisation
{

using FundamentalType = std::variant<bool, std::int64_t, std::uint64_t, float, double, std::string>;

class MORPHEUSCORE_EXPORT JsonReader
{
public:
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

    template<typename T> requires std::is_arithmetic_v<T>
    T read() 
    {
        auto const next = getNext();

        if constexpr (std::is_same_v<bool, T>)
        {
            return std::get<T>(*next);
        }
        else if constexpr (std::integral<T>)
        {
            MORPHEUS_ASSERT((next->index() == 1) or (next->index() == 2));
            return std::visit(functional::Overload{
                [](std::integral auto const value) { return boost::numeric_cast<T>(value); },
                [](auto const& value) -> T { throw value; } // return value; }
            }, *next);
        }
        else
        {
            MORPHEUS_ASSERT((next->index() == 1) or (next->index() == 2) or (next->index() == 3) or (next->index() == 4));
            return std::visit(functional::Overload {
                [](std::integral auto const value) { return boost::numeric_cast<T>(value); },
                [](std::floating_point auto const value) 
                { 
                    if (std::isinf(value)) [[unlikely]]
                    {
                        if (value > 0)
                            return std::numeric_limits<T>::infinity();
                        else
                            return -std::numeric_limits<T>::infinity();
                    }
                    return boost::numeric_cast<T>(value); 
                },
                [](auto const& value) -> T { throw value; } // return value; }
            }, *next);
        }
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

/*cm
    void write(bool const value) {}
    void write(std::uint8_t const value) {}
    void write(std::int8_t const value) {}
    void write(std::uint16_t const value) {}
    void write(std::int16_t const value) {}
    void write(std::uint32_t const value) {}
    void write(std::int32_t const value) {}
    void write(std::uint64_t const value) {}
    void write(std::int64_t const value) {}
    void write(float const value) {}
    void write(double const value) {}
    void write(std::string_view const value) {}
    void write(std::span<std::byte> const value) {}
*/
//private:
//    std::istream& mStream;

private:
    [[nodiscard]] std::optional<FundamentalType> getNext();

    rapidjson::IStreamWrapper mStream;
    rapidjson::Reader mJsonReader;
    std::unique_ptr<class JsonExtracter> mExtractor;
};


}