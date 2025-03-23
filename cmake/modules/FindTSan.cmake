include_guard(GLOBAL)

option(MORPHEUS_THREAD_SANITIZER "Enable ThreadSanitizer for sanitized targets." OFF)

if (NOT MORPHEUS_THREAD_SANITIZER)
    return()
endif()

list(APPEND tsanCandidateFlag "-g -fsanitize=thread") # Gcc & Clang syntax
list(APPEND tsanCandidateFlag "/fsanitize=thread") # MSVC syntax

include(morpheus_check_compiler_flags)
morpheus_check_compiler_flags(
    NAME "Thread Sanitizer"
    PREFIX TSan
    FLAGS ${tsanCandidateFlag}
    RESULT tsanSupported
)

find_package_handle_standard_args(TSan REQUIRED_VARS tsanSupported)

if (TSan_FOUND AND NOT TARGET morpheus::TSan)
    add_library(TSan INTERFACE)
    add_library(morpheus::TSan ALIAS TSan)
    target_compile_options(TSan
        INTERFACE
            #tsanCandidateFlag 
    )
endif()
