#[[
Copyright 2023 Antony Peacock

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
]]

include_guard(GLOBAL)

include(targets)

option(ENABLE_ADDRESS_SANITIZER "Enable AddressSanitizer for sanitized targets." OFF)
option(ENABLE_MEMORY_SANITIZER "Enable MemorySanitizer for sanitized targets." OFF)
option(ENABLE_THREAD_SANITIZER "Enable ThreadSanitizer for sanitized targets." OFF)
option(ENABLE_UNDEFINED_BEHAVIOUR_SANITIZER "Enable UndefineBehaviourSanitizer for sanitized targets." OFF)

if(NOT (ENABLE_ADDRESS_SANITIZER OR ENABLE_MEMORY_SANITIZER OR ENABLE_THREAD_SANITIZER OR ENABLE_UNDEFINED_BEHAVIOUR_SANITIZER))
    return()
endif()

FetchContent_Declare(
    sanitizers
    GIT_REPOSITORY https://github.com/arsenm/sanitizers-cmake
)
FetchContent_GetProperties(sanitizers)
if(NOT sanitizers_POPULATED)
    FetchContent_Populate(sanitizers)
    list(APPEND CMAKE_MODULE_PATH ${sanitizers_SOURCE_DIR}/cmake)
endif()

set(SANITIZE_ADDRESS ${ENABLE_ADDRESS_SANITIZER} CACHE BOOL "Enable AddressSanitizer for sanitized targets." FORCE)
set(SANITIZE_MEMORY ${ENABLE_MEMORY_SANITIZER} CACHE BOOL "Enable MemorySanitizer for sanitized targets." FORCE)
set(SANITIZE_THREAD ${ENABLE_THREAD_SANITIZER} CACHE BOOL "Enable ThreadSanitizer for sanitized targets." FORCE)
set(SANITIZE_UNDEFINED ${ENABLE_UNDEFINED_BEHAVIOUR_SANITIZER} CACHE BOOL "Enable UndefinedBehaviorSanitizer for sanitized targets." FORCE)
find_package(Sanitizers)

targets_get_all(RESULT allTargets DIRECTORY ${PROJECT_SOURCE_DIR})
targets_filter_for_sources(RESULT targetsWithSource TARGETS ${allTargets})
add_sanitizers("${targetsWithSource}")