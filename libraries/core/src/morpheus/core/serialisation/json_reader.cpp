#include "morpheus/core/base/verify.hpp"
#include "morpheus/core/serialisation/read_serialiser.hpp"
#include "morpheus/core/serialisation/json_reader.hpp"

namespace morpheus::serialisation
{

struct JsonExtracter : rapidjson::BaseReaderHandler<rapidjson::UTF8<>, JsonExtracter>
{
    bool Null()
    {
        mCurrent = { JsonReader::Event::Value, std::nullopt };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Bool(bool value)
    { 
        mCurrent = { JsonReader::Event::Value, value };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Int(int value)
    {
        mCurrent = { JsonReader::Event::Value, static_cast<std::int64_t>(value) };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Uint(unsigned value)
    {
        mCurrent = { JsonReader::Event::Value, static_cast<std::uint64_t>(value) };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Int64(int64_t value)
    { 
        mCurrent = { JsonReader::Event::Value, value };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Uint64(uint64_t value)
    { 
        mCurrent = { JsonReader::Event::Value, value };
        return static_cast<Override&>(*this).Default();
    }
    
    bool Double(double value)
    {
        mCurrent = { JsonReader::Event::Value, value };
        return static_cast<Override&>(*this).Default();
    }

    bool RawNumber(const Ch* str, rapidjson::SizeType len, bool copy)
    {
        MORPHEUS_VERIFY(false);
//        mCurrent = std::string(value, len);
        return static_cast<Override&>(*this).Default();
    }

    bool String(const Ch* str, rapidjson::SizeType len, bool)
    {
        mCurrent = { JsonReader::Event::Value, std::string(str, len) };
        return static_cast<Override&>(*this).Default();
    }

    bool StartObject()
    {
        mCurrent = { JsonReader::Event::BeginComposite, std::nullopt };
        return static_cast<Override&>(*this).Default();
    }

    bool Key(const Ch* str, rapidjson::SizeType len, bool copy)
    {
        mCurrent = { JsonReader::Event::BeginComposite, std::string(str, len) };
        return static_cast<Override&>(*this).Default();
    }

    bool EndObject(rapidjson::SizeType)
    {
        mCurrent = { JsonReader::Event::EndComposite, std::nullopt };
        return static_cast<Override&>(*this).Default();
    }

    bool StartArray()
    {
        mCurrent = { JsonReader::Event::BeginSequence, std::nullopt };
        return static_cast<Override&>(*this).Default();
    }

    bool EndArray(rapidjson::SizeType)
    {
        mCurrent = { JsonReader::Event::EndSequence, std::nullopt };
        return static_cast<Override&>(*this).Default();
    }

    JsonReader::EventValue mCurrent;
};

JsonReader::EventValue JsonReader::getNext()
{
    using namespace rapidjson;
    mJsonReader.IterativeParseNext<kParseCommentsFlag | kParseNanAndInfFlag | kParseValidateEncodingFlag >(mStream, *mExtractor);
    if (mJsonReader.HasParseError())
    {
        rapidjson::ParseErrorCode const c = mJsonReader.GetParseErrorCode();
        size_t const o = mJsonReader.GetErrorOffset();
        //std::cout << "PARSE ERROR " << c << " " << o << std::endl;
        //break;
    }
    return mExtractor->mCurrent;
}

JsonReader::JsonReader(std::istream& stream)
:   mStream(stream)
,   mExtractor(std::make_unique<JsonExtracter>())
{
    mJsonReader.IterativeParseInit();
}

JsonReader::~JsonReader()
{
    MORPHEUS_VERIFY(mJsonReader.IterativeParseComplete());
}

void JsonReader::beginComposite()
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::BeginComposite);
}

void JsonReader::endComposite()
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::EndComposite);
}

void JsonReader::beginValue(std::string_view const key)
{
    auto const [event, next] = getNext();
    MORPHEUS_VERIFY(event == Event::BeginComposite);
    MORPHEUS_VERIFY(next);
    MORPHEUS_VERIFY(next->index() == 5);
    MORPHEUS_VERIFY(std::get<std::string>(*next) == key);
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
    //if (null)
    //    beginComposite();
    MORPHEUS_VERIFY(event == Event::Value);
    return !next;
}

void JsonReader::endNullable()
{

}

}