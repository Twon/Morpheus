#pragma once

#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"

#include <catch2/catch_tostring.hpp>

#include <compare>
#include <cstddef>
#include <string>
#include <vector>

namespace morpheus::serialisation::testing
{

struct SimpleTuple
{
    int first = 0;
    bool second = false;
    std::vector<std::byte> data;

    auto operator<=>(SimpleTuple const&) const = default;

    template <concepts::WriteSerialiser Serialiser>
    void serialise(Serialiser& s) const
    {
        s.serialise("first", first);
        s.serialise("second", second);
        s.serialise("data", data);
    }

    template <concepts::ReadSerialiser Serialiser>
    void deserialise(Serialiser& s)
    {
        first = s.template deserialise<decltype(first)>("first");
        second = s.template deserialise<decltype(second)>("second");
        data = s.template deserialise<decltype(data)>("data");
    }
};

} // namespace morpheus::serialisation::testing

/// Specialisation of the formatter for morpheus::serialisation::testing::SimpleTuple to format it as a string.
template <>
struct morpheus::conf::fmt::formatter<morpheus::serialisation::testing::SimpleTuple> : morpheus::conf::fmt::formatter<std::string>
{
    /// Parse the format specifier for morpheus::serialisation::testing::SimpleTuple.
    /// \tparam Context The type of the format context.
    /// \param ctx The format parse context.
    /// \return An iterator to the end of the parsed format specifier.
    template <typename Context>
    constexpr auto parse(Context& context)
    {
        return std::begin(context);
    }

    /// Format the morpheus::application::Version as a string.
    /// \tparam Context The type of the format context.
    /// \param value The version value to format.
    /// \param context The format context.
    template <typename Context>
    constexpr auto format(morpheus::serialisation::testing::SimpleTuple const& value, Context& context) const
    {
        auto out = context.out();
        out = std::format_to(out, "{{first={},second={},data=[", value.first, value.second);

        for (size_t i = 0; i < value.data.size(); ++i)
        {
            if (i > 0)
                out = std::format_to(out, ", ");

            out = std::format_to(out, "{}", std::to_integer<int>(value.data[i]));
        }

        return std::format_to(out, "]}}");
    }
};

template <>
struct ::Catch::StringMaker<morpheus::serialisation::testing::SimpleTuple>
{
    static std::string convert(morpheus::serialisation::testing::SimpleTuple const& t) { return morpheus::conf::fmt::format("{}", t); }
};
