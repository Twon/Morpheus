#pragma once

#include "core/platform.hpp"

namespace mopheus
{

    // clang-format off
    /*! \defgroup Sanitizers Morpheus Supported Sanitizers
            The compiler group of macros allow for compile time detection of the sanitizers
            in the build.
        \note
            https://clang.llvm.org/docs/AddressSanitizer.html#conditional-compilation-with-has-feature-address-sanitizer
            https://docs.microsoft.com/en-us/cpp/sanitizers/asan-building?view=msvc-170
        @{
        \def MORPHEUS_COMPILER_ADDRESS_SANITIZER
            Macro describing the presence of address sanitizer in the build.
        \def MORPHEUS_COMPILER_THREAD_SANITIZER
            Macro describing the presence of thread sanitizer in the build.
    */
    #if defined(__has_feature)
        #if __has_feature(address_sanitizer)
            #define MORPHEUS_COMPILER_ADDRESS_SANITIZER
        #endif
        #if __has_feature(thread_sanitizer)
            #define MORPHEUS_COMPILER_THREAD_SANITIZER
        #endif
    #else
        #ifdef __SANITIZE_ADDRESS__
            #define MORPHEUS_COMPILER_ADDRESS_SANITIZER
        #endif
        #ifdef __SANITIZE_THREAD__
            #define MORPHEUS_COMPILER_THREAD_SANITIZER
        #endif
    #endif
    /// @}

    /*! \def MORPHEUS_NO_SANITIZE_ADDRESS
            Compiler agnostic abstraction of the attibute to eliminate address sanitizer from a method.
    */
    #if (MORPHEUS_IS_GCC_COMPATIBLE_COMPILER)
        // https://clang.llvm.org/docs/AddressSanitizer.html#disabling-instrumentation-with-attribute-no-sanitize-address
        #define MORPHEUS_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
    #else if (MORPHEUS_IS_VISUALSTUDIO_COMPATIBLE_COMPILER)
        // https://docs.microsoft.com/en-us/cpp/sanitizers/asan-building?view=msvc-160
        #define MORPHEUS_NO_SANITIZE_ADDRESS __declspec(no_sanitize_address)
    #else
        #define MORPHEUS_NO_SANITIZE_ADDRESS
    #endif
    // clang-format on

}