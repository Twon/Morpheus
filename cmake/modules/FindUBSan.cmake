include_guard(GLOBAL)

option(MORPHEUS_UNDEFINED_BEHAVIOUR_SANITIZER "Enable UndefineBehaviourSanitizer for sanitized targets." OFF)

if (NOT MORPHEUS_UNDEFINED_BEHAVIOUR_SANITIZER)
    return()
endif()

list(APPEND ubsanCandidateFlag "-g -fsanitize=undefined") # Gcc & Clang syntax
list(APPEND ubsanCandidateFlag "/fsanitize=undefined") # MSVC syntax

include(morpheus_check_compiler_flags)
morpheus_check_compiler_flags(
    NAME "Undefined behavior Sanitizer"
    PREFIX UBSan
    FLAGS ${ubsanCandidateFlag}
    RESULT ubsanSupported
)

find_package_handle_standard_args(UBSan REQUIRED_VARS ubsanSupported)

if (UBSan_FOUND AND NOT TARGET morpheus::UBSan)
    add_library(UBSan INTERFACE)
    add_library(morpheus::UBSan ALIAS UBSan)
    target_compile_options(UBSan
        INTERFACE
            #ubsanCandidateFlag 
    )
endif()
