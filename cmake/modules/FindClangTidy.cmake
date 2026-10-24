#.rst:
# FindClangTidy
# ----------
#
# Try to find clang-tidy
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables::
#
#   ``ClangTidy_EXECUTABLE``
#     The full path to Include What You Use.
#
#   ``ClangTidy_FOUND``
#     True if the Include What You Use executable was found.
#
#   ``ClangTidy_VERSION_STRING``
#      The version of Include What You Use found.
#
include_guard(GLOBAL)

option(CLANG_TIDY_ENABLE "Build with support for Include What You Use" OFF)

set(ClangTidy_VERBOSITY_LEVEL 3 CACHE STRING "Clang Tidy verbosity level (the higher the level, the more output)")

set(LLVM_HINTS)

if(APPLE)
    execute_process(
        COMMAND brew --prefix llvm
        OUTPUT_VARIABLE LLVM_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if(LLVM_PREFIX)
        list(APPEND LLVM_HINTS "${LLVM_PREFIX}/bin")
    endif() 
endif()

find_program(ClangTidy_EXECUTABLE
    NAMES clang-tidy
    HINTS ${LLVM_HINTS}
)

macro(_clang_tidy_log)
    if(NOT CLANG_TIDY_ARGS_QUIET)
        message(STATUS "Morpheus: ${ARGV0}")
    endif()
endmacro()



#[=======================================================================[.rst:
get_clang_tidy_version
------------------

Overview
^^^^^^^^

Gets the version of Clang Tidy.

.. code-block:: cmake

  get_clang_tidy_version(
      [EXECUTABLE <executable path>]
      [RESULT <version result>]
  )

  ``EXECUTABLE``
    The ``EXECUTABLE`` option is required to provide the path to the
    Clang Tidy executable to query.

  ``RESULT``
    The name of the variable to store the version of Clang Tidy to.

#]=======================================================================]
function(get_clang_tidy_version)
    set(options)
    set(oneValueArgs EXECUTABLE RESULT)
    set(multiValueArgs)
    cmake_parse_arguments(CLANG_TIDY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT CLANG_TIDY_EXECUTABLE)
        message(FATAL_ERROR "EXECUTABLE parameter must be supplied")
    endif()
    if (NOT CLANG_TIDY_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    # get version number
    execute_process(COMMAND "${CLANG_TIDY_EXECUTABLE}" --version OUTPUT_VARIABLE versionResults)
    string(REPLACE "\n" ";" versionResults "${versionResults}")
    foreach(LINE ${versionResults})
        string(REGEX MATCH "LLVM version ([\\.0-9]+)" clangTidyResult "${LINE}")
        string(REGEX REPLACE "LLVM version ([\\.0-9]+)" "\\1" clangTidyResult "${clangTidyResult}")
        if(clangTidyResult)
            set(${CLANG_TIDY_RESULT} ${clangTidyResult})
            return(PROPAGATE ${CLANG_TIDY_RESULT})
        endif()
    endforeach()
endfunction()

if(ClangTidy_EXECUTABLE)
    mark_as_advanced(ClangTidy_EXECUTABLE)
    get_clang_tidy_version(EXECUTABLE ${ClangTidy_EXECUTABLE} RESULT ClangTidy_VERSION)
    _clang_tidy_log("clang-tidy version ${ClangTidy_VERSION}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ClangTidy DEFAULT_MSG ClangTidy_EXECUTABLE ClangTidy_VERSION)
mark_as_advanced(ClangTidy_EXECUTABLE ClangTidy_VERSION)




macro(_clang_tidy_args_append arg)
    list(APPEND _clang_tidy_args "${arg}")
endmacro()

#[=======================================================================[.rst:
enable_clang_tidy
------------------

Overview
^^^^^^^^

Sets up the required configuration and enables usage of Clang Tidy via CMake
built in support.

.. code-block:: cmake

  enable_clang_tidy(
      [QUIET]
  )

  ``QUIET``
    The ``QUIET`` option disable logging of iwyu set up details within CMake.

#]=======================================================================]
function(enable_clang_tidy)
    set(options QUIET)
    set(oneValueArgs CONFIG_FILE HEADER_FILTER EXCLUDE_HEADER_FILTER)
    set(multiValueArgs KEEP)
    cmake_parse_arguments(CLANG_TIDY_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT CLANG_TIDY_ENABLE)
        _clang_tidy_log("clang-tidy explicitly disabled with CLAN_TIDY_ENABLE:BOOL=FALSE")
        return()
    endif()

    if(CLANG_TIDY_ARGS_CONFIG_FILE)
        if(NOT EXISTS ${CLANG_TIDY_ARGS_CONFIG_FILE})
            message(FATAL_ERROR "clang-tidy: Config file '${CLANG_TIDY_ARGS_CONFIG_FILE}' does not exist")
        endif()
        _clang_tidy_args_append("--config-file=${CLANG_TIDY_ARGS_CONFIG_FILE}")
    endif()

    if(CLANG_TIDY_ARGS_HEADER_FILTER)
        _clang_tidy_args_append("--header-filter=${CLANG_TIDY_ARGS_HEADER_FILTER}")
    endif()

    if(CLANG_TIDY_ARGS_EXCLUDE_HEADER_FILTER)
        _clang_tidy_args_append("--exclude-header-filter=${CLANG_TIDY_ARGS_EXCLUDE_HEADER_FILTER}")
    endif()

    if(APPLE)
        # Ensure if clang-tidy comes from llvm then we ensure the STL used is from apple-clang
        execute_process(
            COMMAND xcrun --sdk macosx --show-sdk-path
            OUTPUT_VARIABLE MACOS_SDK_PATH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            COMMAND_ERROR_IS_FATAL ANY
        )

        _clang_tidy_args_append("--extra-arg-before=-nostdinc++")
        _clang_tidy_args_append("--extra-arg-before=-isystem")
        _clang_tidy_args_append("--extra-arg-before=${MACOS_SDK_PATH}/usr/include/c++/v1")    
    endif()
    
    set(CMAKE_CXX_CLANG_TIDY "${ClangTidy_EXECUTABLE};-p=${CMAKE_BINARY_DIR};${_clang_tidy_args}" PARENT_SCOPE)

    _clang_tidy_log("  Arguments: ${_clang_tidy_args}")
    _clang_tidy_log("Enabling clang-tidy - done")
endfunction()

if (CLANG_TIDY_ENABLE)
    enable_clang_tidy(
        CONFIG_FILE ${PROJECT_SOURCE_DIR}/.clang-tidy
        #EXCLUDE_HEADER_FILTER ".*/.conan2/.*"
    )
endif()
