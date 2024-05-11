include_guard(GLOBAL)

option(MORPHEUS_MEMORY_SANITIZER "Enable MemorySanitizer for sanitized targets." OFF)

if (NOT MORPHEUS_MEMORY_SANITIZER)
    return()
endif()

list(APPEND msanCandidateFlag "-g -fsanitize=memory") # Gcc & Clang syntax
list(APPEND msanCandidateFlag "/fsanitize=memory") # MSVC syntax

include(morpheus_check_compiler_flags)
morpheus_check_compiler_flags(
    NAME "Thread Sanitizer"
    PREFIX MSan
    FLAGS ${msanCandidateFlag}
    RESULT msanSupported
)

find_package_handle_standard_args(TSan REQUIRED_VARS msanSupported)

if (MSan_FOUND AND NOT TARGET morpheus::MSan)
    add_library(MSan INTERFACE)
    add_library(morpheus::MSan ALIAS MSan)
    target_compile_options(MSan
        INTERFACE
            #msanCandidateFlag 
    )
endif()