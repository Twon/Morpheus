#pragma once

#include "morpheus/core/base/assert.hpp"
#include "morpheus/core/base/scoped_action.hpp"
#include "morpheus/core/concurrency/generator.hpp"
#include "morpheus/core/functional/overload.hpp"
#include "morpheus/core/serialisation/concepts/reader_archtype.hpp"
#include "morpheus/core/serialisation/read_serialiser_decl.hpp"

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
///     Read in objects from an underlying json representation. 
class MORPHEUSCORE_EXPORT JsonReader
{
    [[nodiscard]] auto currentState()
    {
        return ScopedAction(
            [&]() { if (!mCurrent) mCurrent = getNext();  return *mCurrent; },
            [&]() { mCurrent.reset(); }
        );
    }
public:
    /// \class Exception
    ///     Exception type to be thrown for errors when parsing JSON.
    class Exception : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

    static constexpr bool canBeTextual() { return true; }
    static constexpr bool isTextual() { return true; }

    /// Json reader take in a stream of json to extract data members from.
    /// \param[in] stream Stream used to read in the json source.  This must outlive the reader as its held by referece.
    explicit JsonReader(std::istream& stream);
    ~JsonReader();

    void beginComposite();
    void endComposite();
    void beginValue(std::string_view const key);
    void endValue();
    std::optional<std::size_t> beginSequence();
    void endSequence();
    bool beginNullable();
    void endNullable();

    template<typename T> requires requires(concepts::ReaderArchtype& r) { { r.template read<T>() } ->std::same_as<T>; }
    auto readSequence()//std::invocable auto serialiser)
    {
        return [&/*, serialiser = std::move(serialiser)*/]() -> concurrency::Generator<T>
            {
                beginSequence();
                for(;;)
                { 
                    auto const state = currentState();
                    auto const [event, next] = state.value();
                    if (event == Event::EndSequence)
                        co_return;

                    MORPHEUS_ASSERT(event == Event::Value);
                    co_yield read<T>();
                    //co_yield serialiser();
                }
            };
    }

    template<typename T> requires std::is_same_v<T, bool>
    T read()
    {
        auto const state = currentState();
        auto const [event, next] = state.value();
        MORPHEUS_ASSERT(next->index() == 0);
        return std::get<T>(*next);
    }

    template<std::integral Interger> requires (not std::is_same_v<bool, Interger>)
    Interger read()
    {
        auto const state = currentState();
        auto const [event, next] = state.value();
        MORPHEUS_ASSERT((next->index() == 1) or (next->index() == 2));
        return std::visit(functional::Overload{
            [](std::integral auto const value) { return boost::numeric_cast<Interger>(value); },
            [](auto const value) -> Interger { throw Exception("Unable to convert to integral point representation"); }
        }, *next);
    }

    template<std::floating_point Float>
    Float read()
    {
        auto const state = currentState();
        auto const [event, next] = state.value();
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
        auto const state = currentState();
        auto const [event, next] = state.value();
        MORPHEUS_ASSERT(next->index() == 5);
        return std::get<T>(*next);
    }

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

/* [[nodiscard]] auto currentState()
    {
        return ScopedAction(
//            [&]() { return getCurrent(); },
//            [&]() { clearCurrent(); }
            [&]() 
            {
                if (!mCurrent) mCurrent = getNext();
                return *mCurrent;
            },
            [&]() { mCurrent.reset(); }
        );
    }*/

/*  
    EventValue& getCurrent()
    {
        if (!mCurrent)
            mCurrent = getNext();
        return *mCurrent;
    }
    void clearCurrent() { mCurrent.reset(); }
*/

    rapidjson::IStreamWrapper mStream;
    rapidjson::Reader mJsonReader;
    std::unique_ptr<class JsonExtracter> mExtractor;
    std::optional<EventValue> mCurrent;
};


}