#pragma once

#include <morpheus/core/base/platform.hpp>

/// Ensure backware compatible support for __has_include
#ifndef __has_include
    #define __has_include(x) 0
#endif

/// \note
///     #include <version> on Windows can accidentally picks up VERSION files.  Use the old <ciso646>
///     instead.  For details see: https://bugs.llvm.org/show_bug.cgi?id=42540
//#if __has_include(<version>) && (MORPHEUS_BUILD_PLATFORM == MORPHEUS_TARGET_PLATFORM_PC_WINDOWS)
    #include <version>
//#else
//    #include <ciso646>
//#endif
