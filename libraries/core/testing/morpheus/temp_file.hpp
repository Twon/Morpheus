
#pragma once

#include "morpheus/core/base/compiler.hpp"
#include "morpheus/core/base/verify.hpp"

#include <cstdio>
#include <stdio.h>
#include <string>

namespace morpheus
{

/// \class TempFile
///     Testing fixture which when used as or in a specific test fixture disable logging output and renables it at the end of the fixture scope.
class TempFile
{
public:
    TempFile()
    : mFile(
          []
          {
#if MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER
              std::FILE* file = nullptr;
              MORPHEUS_VERIFY(tmpfile_s(&file) == 0);
              return file;
#else
              return std::tmpfile();
#endif
          }())
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
        MORPHEUS_VERIFY(std::fread(contents.data(), sizeof(char), contents.size(), mFile) == contents.size());
        std::fseek(mFile, 0, SEEK_END);
        return contents;
    }
private:
    std::string mPath;
    std::FILE* mFile;
};

} // namespace morpheus
