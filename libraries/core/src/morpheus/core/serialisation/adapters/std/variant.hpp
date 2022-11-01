#pragma once

#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/conformance/ranges.hpp"
#include "morpheus/core/meta/is_specialisation.hpp"
#include "morpheus/core/serialisation/concepts/read_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/read_serialisable.hpp"
#include "morpheus/core/serialisation/concepts/write_serialiser.hpp"
#include "morpheus/core/serialisation/concepts/write_serialisable.hpp"

#include <array>
#include <stdexcept>
#include <typeinfo>
#include <variant>

namespace morpheus::serialisation::detail
{

template <typename T>
concept IsStdVariant = meta::IsSpecialisationOf<std::variant, T>;

template <typename T>
struct TypeListNames;

template <typename... T>
struct TypeListNames<std::variant<T...>>
{
    static constexpr std::string_view name(std::size_t const entry)
    {
        MORPHEUS_ASSERT(entry < sizeof...(T));
        return typeNames[entry];
    }

    static consteval std::string_view findIndex(std::string_view const name)
    {
        auto const entry = ranges::find(typeNames, name);
        if (entry == typeNames.end())
            throw std::out_of_range(fmt_ns::format("{} is not a valid type name.", name));
        return std::distance(typeNames.begin(),entry);
    }

    inline static std::array<std::string, sizeof...(T)> typeNames{ typeid(T).name()...};
};

template<concepts::WriteSerialiser Serialiser, concepts::WriteSerialisable... T>
void serialise(Serialiser& serialiser, std::variant<T...> const& value)
{
    serialiser.serialise([&]()
    {
        if (value.valueless_by_exception()) [[unlikely]]
        {
            serialiser.serialise("index", static_cast<std::uint64_t>(std::variant_npos));
        }
        else
        {
            if (serialiser.writer().isTextual())
            {
                serialiser.serialise("type", TypeListNames<std::variant<T...>>::name(value.index()));
            }
            else
                serialiser.serialise("index", static_cast<std::uint64_t>(value.index()));

            std::visit([&serialiser](auto const& value) { return serialiser.serialise("value", value); }, value);
        }
    });
}

template<concepts::ReadSerialiser Serialiser, IsStdVariant T>
T deserialise(Serialiser& serialiser)
{
    auto const scope = makeScopedComposite(serialiser.reader());
    auto const index = [&serialiser]
    {
        if (serialiser.reader().isTextual())
            return serialiser.template deserialise<std::uint64_t>("index");
        else
        {
            auto const type = serialiser.template deserialise<std::string>("type");
            return TypeListNames<T>::findIndex(type);
        }
    }();
    [&serialiser]<std::size_t... Indexes>(std::index_sequence<Indexes...>)
    {
//        static_assert((!std::is_reference_v<std::tuple_element_t<Indexes, T>> || ...));

        return T{ serialiser.template deserialise<std::tuple_element_t<Indexes, T>>()... };
    }(std::make_index_sequence<std::variant_size_v<T>>());

    return T{};
}

} // morpheus::serialisation