
#pragma once

#include <cstdio>
#include <string>

namespace morpheus
{

/// \class TempFile
///     Testing fixture which when used as or in a specific test fixture disable logging output and renables it at the end of the fixture scope.
class TempFile
{
public:
    TempFile()
    : mFile(std::tmpfile())
    {
    }
    
    ~TempFile()
    {
        // tempfile automatically deletes the file on close.
        std::fclose(mFile);
    }

    auto getFile() const { return mFile; }

    auto contents()
    {
        std::fseek(mFile, 0, SEEK_END); 
        std::size_t const filesize = std::ftell(mFile);
        std::string contents(filesize, 0);
        std::fseek(mFile, 0, SEEK_SET); // seek to start
        std::fread(contents.data(), sizeof(char), contents.size(), mFile);
        std::fseek(mFile, 0, SEEK_END); 
        return contents;
    }
private:
    std::string mPath;
    std::FILE* mFile;
};

} // namespace morpheus