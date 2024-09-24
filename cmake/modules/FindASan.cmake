include_guard(GLOBAL)

option(MORPHEUS_ADDRESS_SANITIZER "Enable AddressSanitizer for sanitized targets." OFF)

if (NOT MORPHEUS_ADDRESS_SANITIZER)
    return()
endif()

if (MORPHEUS_ADDRESS_SANITIZER AND (MORPHEUS_MEMORY_SANITIZER OR MORPHEUS_THREAD_SANITIZER))
    message(FATAL_ERROR "morpheus: AddressSanitizer is not compatible with ThreadSanitizer or MemorySanitizer.")
endif ()

# For gcc and clang first attempt to sanitize address with full frame pointer information.
list(APPEND asanCandidateFlag "-g -fsanitize=address -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer") 
list(APPEND asanCandidateFlag "-g -fsanitize=address -fno-omit-frame-pointer")
list(APPEND asanCandidateFlag "-g -fsanitize=address")
list(APPEND asanCandidateFlag "/fsanitize=address") # MSVC syntax

include(morpheus_check_compiler_flags)
morpheus_check_compiler_flags(
    NAME "Address Sanitizer"
    PREFIX ASan
    FLAGS ${asanCandidateFlag}
    RESULT asanSupported
)

find_package_handle_standard_args(ASan REQUIRED_VARS asanSupported)

if (ASan_FOUND AND NOT TARGET ASan::ASan)
    add_library(ASan INTERFACE)
    add_library(morpheus::ASan ALIAS ASan)
    target_compile_options(ASan
        INTERFACE
            
    )
endif()

