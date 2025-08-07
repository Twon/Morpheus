#pragma once

#include <ostream>
#include <sstream>
#include <streambuf>

namespace morpheus
{

/// \struct RedirectStream
///     Testing fixture which when used as or in a specific test fixture redirects the output of a stream and re-enables it at the end of the fixture scope.
struct RedirectStream
{
    /// Redirect stream to string stream on construction.
    RedirectStream(std::ostream& stream)
        : mStream(stream)
        , mPrevious(mStream.rdbuf(mStringStream.rdbuf()))
    {}

    /// The output captured by the stream.
    auto getOutput() const { return mStringStream.str(); }

    /// Restore previous stream state on destruction.
    ~RedirectStream() { mStream.rdbuf(mPrevious); }

private:
    std::ostream& mStream;
    std::stringstream mStringStream;
    std::streambuf* mPrevious;
};

} // namespace morpheus
