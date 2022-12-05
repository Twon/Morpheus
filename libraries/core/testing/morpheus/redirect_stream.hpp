#pragma once

#include <ostream>
#include <sstream>
#include <streambuf>

namespace morpheus
{

struct RedirectStream
{
    // Redirect stream to string stream on construction
    RedirectStream(std::ostream& stream)
    :   mStream(stream)
    ,   mPrevious(mStream.rdbuf(mStringStream.rdbuf()))
    { }

    auto getOutput() const { return mStringStream.str(); }

    // Restore previous stream state on destruction
    ~RedirectStream()
    {
        mStream.rdbuf(mPrevious);
    }

private:
    std::ostream& mStream;
    std::stringstream mStringStream;
    std::streambuf* mPrevious;
};


} // namespace morpheus