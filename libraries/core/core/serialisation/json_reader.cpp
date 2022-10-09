#include "core/base/verify.hpp"
#include "core/serialisation/read_serialiser.hpp"
#include "core/serialisation/json_reader.hpp"




namespace morpheus::serialisation
{

struct JsonExtracter : rapidjson::BaseReaderHandler<rapidjson::UTF8<>, JsonExtracter>
{
    bool Null()
    {
        mCurrent = std::nullopt;
        return static_cast<Override&>(*this).Default();
    }
    
    bool Bool(bool value)
    { 
        mCurrent = value;
        return static_cast<Override&>(*this).Default();
    }
    
    bool Int(int value)
    {
        mCurrent = static_cast<std::int64_t>(value);
        return static_cast<Override&>(*this).Default();
    }
    
    bool Uint(unsigned value)
    {
        mCurrent = static_cast<std::uint64_t>(value);
        return static_cast<Override&>(*this).Default();
    }
    
    bool Int64(int64_t value)
    { 
        mCurrent = value;
        return static_cast<Override&>(*this).Default();
    }
    
    bool Uint64(uint64_t value)
    { 
        mCurrent = value;
        return static_cast<Override&>(*this).Default();
    }
    
    bool Double(double value)
    {
        mCurrent = value;
        return static_cast<Override&>(*this).Default();
    }

    bool RawNumber(const Ch* str, rapidjson::SizeType len, bool copy) // { return static_cast<Override&>(*this).String(str, len, copy); }
    {
//        mCurrent = std::string(value, len);
        return static_cast<Override&>(*this).Default();
    }

    bool String(const Ch* str, rapidjson::SizeType len, bool)
    {
        mCurrent = std::string(str, len);
        return static_cast<Override&>(*this).Default();
    }

    bool StartObject()
    {
        return static_cast<Override&>(*this).Default();
    }

    bool Key(const Ch* str, rapidjson::SizeType len, bool copy)
    {
        return static_cast<Override&>(*this).Default();
    }

    bool EndObject(rapidjson::SizeType)
    {
        return static_cast<Override&>(*this).Default();
    }

    bool StartArray()
    {
        return static_cast<Override&>(*this).Default();
    }

    bool EndArray(rapidjson::SizeType)
    {
        return static_cast<Override&>(*this).Default();
    }

    using ExtractedType = std::optional<FundamentalType>;

    ExtractedType mCurrent;
};

std::optional<FundamentalType> JsonReader::getNext()
{
    mJsonReader.IterativeParseNext<rapidjson::kParseCommentsFlag | rapidjson::kParseNanAndInfFlag>(mStream, *mExtractor);
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
}

void JsonReader::endComposite()
{
}

void JsonReader::beginValue(std::string_view const key)
{
}

void JsonReader::endValue()
{
}

void JsonReader::beginSequence(std::optional<std::size_t>)
{
}

void JsonReader::endSequence()
{
}

}