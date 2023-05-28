#include "morpheus/core/serialisation/json_reader.hpp"
#include "morpheus/core/base/exceptions.hpp"
#include "morpheus/core/base/verify.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"

// #include <magic_enum_format.hpp>

namespace morpheus::serialisation
{

namespace
{

void checkExpectedEvent(auto const event, auto const expected)
{
    if (event != expected)
        throwRuntimeException(fmt_ns::format("{} expected, but {} encountered", magic_enum::enum_name(expected), magic_enum::enum_name(event)));
}

} // namespace

/// \struct JsonExtracter
///     Specialisation of rapidjson::BaseReaderHandler to extract values from a Json stream.
struct JsonExtracter : rapidjson::BaseReaderHandler<rapidjson::UTF8<>, JsonExtracter>
{
    /// Null value encountered.
    bool Null()
    {
        mCurrent = {JsonReader::Event::Value, std::nullopt};
        return static_cast<Override&>(*this).Default();
    }

    /// Boolean value encountered.
    bool Bool(bool value)
    {
        mCurrent = {JsonReader::Event::Value, value};
        return static_cast<Override&>(*this).Default();
    }

    /// Integer value encountered.
    bool Int(int value)
    {
        mCurrent = {JsonReader::Event::Value, static_cast<std::int64_t>(value)};
        return static_cast<Override&>(*this).Default();
    }

    /// Unsigned integer value encountered.
    bool Uint(unsigned value)
    {
        mCurrent = {JsonReader::Event::Value, static_cast<std::uint64_t>(value)};
        return static_cast<Override&>(*this).Default();
    }

    /// 64-bit integer value encountered.
    bool Int64(int64_t value)
    {
        mCurrent = {JsonReader::Event::Value, value};
        return static_cast<Override&>(*this).Default();
    }

    /// 64-bit unsigned integer value encountered.
    bool Uint64(uint64_t value)
    {
        mCurrent = {JsonReader::Event::Value, value};
        return static_cast<Override&>(*this).Default();
    }

    /// Double value encountered.
    bool Double(double value)
    {
        mCurrent = {JsonReader::Event::Value, value};
        return static_cast<Override&>(*this).Default();
    }

    /// Raw number value encountered.
    bool RawNumber(const Ch* str, rapidjson::SizeType len, bool copy)
    {
        MORPHEUS_VERIFY(false);
        //        mCurrent = std::string(value, len);
        return static_cast<Override&>(*this).Default();
    }

    /// String value encountered.
    bool String(const Ch* str, rapidjson::SizeType len, bool)
    {
        mCurrent = {JsonReader::Event::Value, std::string(str, len)};
        return static_cast<Override&>(*this).Default();
    }

    /// Start of an object encountered.
    bool StartObject()
    {
        mCurrent = {JsonReader::Event::BeginComposite, std::nullopt};
        return static_cast<Override&>(*this).Default();
    }

    /// Key value mapping type encountered.
    bool Key(const Ch* str, rapidjson::SizeType len, bool copy)
    {
        mCurrent = {JsonReader::Event::BeginComposite, std::string(str, len)};
        return static_cast<Override&>(*this).Default();
    }

    /// End of an object encountered.
    bool EndObject(rapidjson::SizeType)
    {
        mCurrent = {JsonReader::Event::EndComposite, std::nullopt};
        return static_cast<Override&>(*this).Default();
    }

    /// Start of an array encountered.
    bool StartArray()
    {
        mCurrent = {JsonReader::Event::BeginSequence, std::nullopt};
        return static_cast<Override&>(*this).Default();
    }

    /// End of an array encountered.
    bool EndArray(rapidjson::SizeType)
    {
        mCurrent = {JsonReader::Event::EndSequence, std::nullopt};
        return static_cast<Override&>(*this).Default();
    }

    JsonReader::EventValue mCurrent; ///< Current json event.
};



JsonReader::EventValue JsonReader::getNext()
{
    using namespace rapidjson;
    mJsonReader.IterativeParseNext<kParseCommentsFlag | kParseNanAndInfFlag | kParseValidateEncodingFlag>(mStream, *mExtractor);
    if (mJsonReader.HasParseError()) {
        rapidjson::ParseErrorCode const c = mJsonReader.GetParseErrorCode();
        size_t const o = mJsonReader.GetErrorOffset();
        // std::cout << "PARSE ERROR " << c << " " << o << std::endl;
        // break;
    }
    return mExtractor->mCurrent;
}

JsonReader::JsonReader(std::istream& stream, bool validate)
: mStream(stream)
, mExtractor(std::make_unique<JsonExtracter>())
, mValidate(validate)
{
    mJsonReader.IterativeParseInit();
}

JsonReader::~JsonReader()
{
    if (mValidate)
        MORPHEUS_VERIFY(mJsonReader.IterativeParseComplete());
}

void JsonReader::beginComposite()
{
    auto const [event, next] = getNext();
    checkExpectedEvent(event, Event::BeginComposite);
}

void JsonReader::endComposite()
{
    auto const [event, next] = getNext();
    checkExpectedEvent(event, Event::EndComposite);
}

void JsonReader::beginValue(std::string_view const key)
{
    auto const [event, next] = getNext();
    checkExpectedEvent(event, Event::BeginComposite);

    if (!next)
        throwRuntimeException("Unexpected empty composite");

    if (next->index() != magic_enum::enum_integer(FundamentalType::String)) {
        auto const type = magic_enum::enum_cast<FundamentalType>(next->index());
        MORPHEUS_ASSERT(type);
        throwRuntimeException(fmt_ns::format("Expect composite value, expected was type String actual was {}", magic_enum::enum_name(*type)));
    }

    if (std::get<std::string>(*next) != key)
        throwRuntimeException(fmt_ns::format("Expected key {} does not match actual key {}", key, std::get<std::string>(*next)));
}

void JsonReader::endValue()
{
    //    auto const [event, next] = getNext();
    //    MORPHEUS_VERIFY(event == Event::EndComposite);
}

void JsonReader::beginSequence(std::optional<std::size_t>)
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::BeginSequence);
}

void JsonReader::endSequence()
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::EndSequence);
}

bool JsonReader::beginNullable()
{
    auto const [event, next] = getNext();
    // if (null)
    //     beginComposite();
    MORPHEUS_VERIFY(event == Event::Value);
    return !next;
}

void JsonReader::endNullable() {}

} // namespace morpheus::serialisation