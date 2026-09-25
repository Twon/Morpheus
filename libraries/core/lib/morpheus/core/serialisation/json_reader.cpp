#include "morpheus/core/base/verify.hpp"
#include "morpheus/core/conformance/format.hpp"
#include "morpheus/core/serialisation/json_reader.hpp"

#include <rapidjson/encodings.h>
#include <rapidjson/error/error.h>
#include <rapidjson/rapidjson.h>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include <algorithm>
#include <istream>
#include <utility>

namespace morpheus::serialisation
{

namespace
{

void checkExpectedEvent(auto const event, auto const expected)
{
    if (event != expected)
        throwJsonException("{} expected, but {} encountered", magic_enum::enum_name(expected), magic_enum::enum_name(event));
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
    bool RawNumber(Ch const*, rapidjson::SizeType, bool /*copy*/)
    {
        // Method enabled via kParseNumbersAsStringsFlag.
        MORPHEUS_VERIFY(false);
        //        mCurrent = std::string(str, len);
        return static_cast<Override&>(*this).Default();
    }

    /// String value encountered.
    bool String(Ch const* str, rapidjson::SizeType len, bool)
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
    bool Key(Ch const* str, rapidjson::SizeType len, bool /*copy*/)
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

    if (mPendingEvent)
    {
        auto result = std::move(*mPendingEvent);
        mPendingEvent.reset();
        return result;
    }

    mJsonReader->IterativeParseNext<kParseCommentsFlag | kParseNanAndInfFlag | kParseValidateEncodingFlag>(*mStream, *mExtractor);
    if (mJsonReader->HasParseError())
    {
        rapidjson::ParseErrorCode const c = mJsonReader->GetParseErrorCode();
        size_t const o = mJsonReader->GetErrorOffset();
        throwJsonException("Parse error at offset {}, error {}", o, magic_enum::enum_name(c));
    }
    return mExtractor->mCurrent;
}

JsonReader::EventValue const& JsonReader::peekNext()
{
    using namespace rapidjson;

    if (!mPendingEvent)
    {
        mJsonReader->IterativeParseNext<kParseCommentsFlag | kParseNanAndInfFlag | kParseValidateEncodingFlag>(*mStream, *mExtractor);
        if (mJsonReader->HasParseError())
        {
            rapidjson::ParseErrorCode const c = mJsonReader->GetParseErrorCode();
            size_t const o = mJsonReader->GetErrorOffset();
            throwJsonException("Parse error at offset {}, error {}", o, magic_enum::enum_name(c));
        }
        mPendingEvent = mExtractor->mCurrent;
    }
    return *mPendingEvent;
}

bool JsonReader::isAtEndSequence()
{
    auto const& [event, value] = peekNext();
    return event == Event::EndSequence;
}

JsonReader::JsonReader(std::istream& stream, bool validate)
    : mSourceStream(stream)
    , mStream(std::make_unique<rapidjson::IStreamWrapper>(mSourceStream.get()))
    , mJsonReader(std::make_unique<rapidjson::Reader>())
    , mExtractor(std::make_unique<JsonExtracter>())
    , mValidate(validate)
{
    mJsonReader->IterativeParseInit();
}

JsonReader::JsonReader(JsonReader&& rhs) noexcept = default;
JsonReader& JsonReader::operator=(JsonReader&& rhs) noexcept = default;

JsonReader::~JsonReader()
{
    if (mValidate)
        MORPHEUS_VERIFY(mJsonReader->IterativeParseComplete());
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
        throwJsonException("Unexpected empty composite");

    if (std::get<std::string>(*next) != key)
        throwJsonException("Expected key {} does not match actual key {}", key, std::get<std::string>(*next));
}

void JsonReader::endValue()
{
    //    auto const [event, next] = getNext();
    //    MORPHEUS_VERIFY(event == Event::EndComposite);
}

std::optional<std::size_t> JsonReader::beginSequence()
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::BeginSequence);
    return std::nullopt;
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

std::vector<std::byte> JsonReader::readBytes()
{
    auto encoded = read<std::string>();

    // Base64 padding characters '=' must be removed before decoding with boost iterators
    encoded.erase(std::remove(encoded.begin(), encoded.end(), '='), encoded.end());

    using namespace boost::archive::iterators;
    typedef transform_width<binary_from_base64<std::string::const_iterator>, 8, 6> base64_dec;

    std::vector<std::byte> decoded;
    try
    {
        decoded.reserve((encoded.size() * 3) / 4);
        std::transform(base64_dec(encoded.begin()), base64_dec(encoded.end()), std::back_inserter(decoded), [](auto c) { return static_cast<std::byte>(c); });
    }
    catch (std::exception const& e)
    {
        throwJsonException("Failed to decode Base64 string: {}", e.what());
    }

    return decoded;
}

} // namespace morpheus::serialisation
