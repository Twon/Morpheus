#.rst:
# FindIWYU
# ----------
#
# Try to find Include What You Use
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables::
#
#   ``IWYU_EXECUTABLE``
#     The full path to Include What You Use.
#
#   ``IWYU_FOUND``
#     True if the Include What You Use executable was found.
#
#   ``IWYU_VERSION_STRING``
#      The version of Include What You Use found.
#
include_guard(GLOBAL)

option(IWYU_ENABLE "Build with support for Include What You Use" OFF)

set(IWYU_VERBOSITY_LEVEL 3 CACHE STRING "IWYU verbosity level (the higher the level, the more output)")

find_program(IWYU_EXECUTABLE
    NAMES include-what-you-use
)

macro(_iwyu_log)
    if(NOT IWYU_QUIET)
        message(STATUS "Morpheus: ${ARGV0}")
    endif()
endmacro()



#[=======================================================================[.rst:
get_iwyu_version
------------------
Overview
^^^^^^^^
Gets the version of Include What You Use.
.. code-block:: cmake
  get_iwyu_version(
      [EXECUTABLE <executable path>]
      [RESULT <version result>]
  )
  ``EXECUTABLE``
    The ``EXECUTABLE`` option is required to provide the path to the
    Include What You Use executable to query.
  ``RESULT``
    The name of the variable to store the version of Include What You Use
    to.
#]=======================================================================]
function(get_iwyu_version)
    set(options)
    set(oneValueArgs EXECUTABLE RESULT)
    set(multiValueArgs)
    cmake_parse_arguments(IWYU "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT IWYU_EXECUTABLE)
        message(FATAL_ERROR "EXECUTABLE parameter must be supplied")
    endif()
    if (NOT IWYU_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    # get version number
    execute_process(COMMAND "${IWYU_EXECUTABLE}" --version OUTPUT_VARIABLE versionResults)
    string(REPLACE "\n" ";" versionResults "${versionResults}")
    foreach(LINE ${versionResults})
        string(REGEX MATCH "include-what-you-use ([\\.0-9]+)" iwyuResult "${LINE}")
        string(REGEX REPLACE "include-what-you-use ([\\.0-9]+)" "\\1" iwyuResult "${iwyuResult}")
        if(iwyuResult)
            set(${IWYU_RESULT} ${iwyuResult})
            return(PROPAGATE ${IWYU_RESULT})
        endif()
    endforeach()
endfunction()

if(IWYU_EXECUTABLE)
    mark_as_advanced(IWYU_EXECUTABLE)
    get_iwyu_version(EXECUTABLE ${IWYU_EXECUTABLE} RESULT IWYU_VERSION)
    _iwyu_log("include-what-you-use version ${IWYU_VERSION}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IWYU DEFAULT_MSG IWYU_EXECUTABLE IWYU_VERSION)
mark_as_advanced(IWYU_EXECUTABLE IWYU_VERSION)




macro(_iwyu_args_append arg)
    list(APPEND _iwyu_args "-Xiwyu" "${arg}")
endmacro()

macro(_iwyu_args_append_if_present option arg)
    if(IWYU_ARGS_${option})
        _iwyu_args_append("${arg}")
    endif()
endmacro()

#[=======================================================================[.rst:
enable_iwyu
------------------
Overview
^^^^^^^^
Sets up the required configuration and enables usage of Include What You Use via
CMake built in support.
.. code-block:: cmake
  enable_iwyu(
      [REQUIRED]
      [QUIET]
      [ERROR]
      [NO_DEFAULT_MAPPINGS]
      [PCH_IN_CODE]
      [TRANSITIVE_INCLUDES_ONLY]
      [NO_COMMENTS]
      [NO_FORWARD_DECLARATIONS]
      [CXX17_NAMESPACES]
      [QUOTED_INCLUDES_FIRST]
      [QUOTED_INCLUDES_FIRST]
      [MAPPING_FILE <mapping file>]
      [MAX_LINE_LENGTH <length>]
      [KEEP <glob...>]
  )
  ``REQUIRED``
    The ``REQUIRED`` option causes an error to be raised if iwyu is not found.
  ``QUIET``
    The ``QUIET`` option disable logging of iwyu set up details within CMake.
  ``ERROR``
    Exit with N (default: 1) for iwyu violations.
  ``NO_DEFAULT_MAPPINGS``
    Do not add iwyu's default mappings.
  ``PCH_IN_CODE``
    Mark the first include in a translation unit as a precompiled header.  Use --pch_in_code to prevent IWYU from
    removing necessary PCH includes.  Though Clang forces PCHs to be listed as prefix headers, the PCH-in-code
    pattern can be used with GCC and is standard practice on MSVC (e.g. stdafx.h)
  ``TRANSITIVE_INCLUDES_ONLY``
    Do not suggest that a file add foo.h unless foo.h is already visible in the file's transitive includes.
  ``NO_COMMENTS``
    Do not add 'why' comments.
  ``NO_FORWARD_DECLARATIONS``
    Do not use forward declarations.
  ``CXX17_NAMESPACES``
    Suggests the more concise syntax introduced in C++17.
  ``QUOTED_INCLUDES_FIRST``
    When sorting includes, place quoted ones first.
  ``MAPPING_FILE``
    Gives iwyu a mapping file.
  ``MAX_LINE_LENGTH``
    Maximum line length for includes. Note that this only affects comments and alignment thereof,
    the maximum line length can still be exceeded with long file names (default: 80).
  ``KEEP``
    Tells iwyu to always keep these includes. This flag may be specified multiple times to specify multiple
    glob patterns.
#]=======================================================================]
function(enable_iwyu)
    set(options QUIET REQUIRED ERROR NO_DEFAULT_MAPPINGS PCH_IN_CODE TRANSITIVE_INCLUDES_ONLY NO_COMMENTS NO_FORWARD_DECLARATIONS CXX17_NAMESPACES QUOTED_INCLUDES_FIRST)
    set(oneValueArgs MAPPING_FILE MAX_LINE_LENGTH VERBOSITY_LEVEL)
    set(multiValueArgs KEEP)
    cmake_parse_arguments(IWYU_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(IWYU_ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Invalid arguments '${IWYU_ARGS_UNPARSED_ARGUMENTS}'")
    endif()

    if(IWYU_ARGS_KEYWORDS_MISSING_VALUES)
        message(FATAL_ERROR "No value provided for '${IWYU_ARGS_KEYWORDS_MISSING_VALUES}'")
    endif()

    if (NOT IWYU_ENABLE)
        _iwyu_log("include-what-you-use explicitly disabled with IWYU_ENABLE:BOOL=FALSE")
        return()
    endif()

    if(IWYU_ARGS_KEEP)
        foreach(pattern ${IWYU_ARGS_KEEP})
            _iwyu_args_append("--keep=${pattern}")
        endforeach()
    endif()

    if(IWYU_ARGS_MAPPING_FILE)
        if(NOT EXISTS ${IWYU_ARGS_MAPPING_FILE})
            message(FATAL_ERROR "IWYU: Mapping file '${IWYU_ARGS_MAPPING_FILE}' does not exist")
        endif()
        _iwyu_args_append("--mapping_file=${IWYU_ARGS_MAPPING_FILE}")
    endif()

    if(IWYU_ARGS_MAX_LINE_LENGTH)
        if(NOT IWYU_ARGS_MAX_LINE_LENGTH GREATER 0)
            message(FATAL_ERROR "IWYU: Invalid MAX_LINE_LENGTH value = '${IWYU_ARGS_MAX_LINE_LENGTH}")
        endif()
        _iwyu_args_append("--max_line_length=${IWYU_ARGS_MAX_LINE_LENGTH}")
    endif()

    _iwyu_args_append_if_present(ERROR "--error")
    _iwyu_args_append_if_present(NO_DEFAULT_MAPPINGS "--no_default_mappings")
    _iwyu_args_append_if_present(PCH_IN_CODE "--pch_in_code")
    _iwyu_args_append_if_present(TRANSITIVE_INCLUDES_ONLY "--transitive_includes_only")
    _iwyu_args_append_if_present(NO_COMMENTS "--no_comments")
    _iwyu_args_append_if_present(NO_FORWARD_DECLARATIONS "--no_fwd_decls")
    _iwyu_args_append_if_present(CXX17_NAMESPACES "--cxx17ns")
    _iwyu_args_append_if_present(QUOTED_INCLUDES_FIRST "--quoted_includes_first")

    if(IWYU_ARGS_VERBOSITY_LEVEL)
        _iwyu_args_append("--verbose=${IWYU_ARGS_VERBOSITY_LEVEL}")
    endif()

    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXECUTABLE};${_iwyu_args}" PARENT_SCOPE)

    _iwyu_log("  Arguments: ${_iwyu_args}")
    _iwyu_log("Enabling include-what-you-use - done")
endfunction()

if (IWYU_ENABLE)
    enable_iwyu(
        QUOTED_INCLUDES_FIRST
        MAX_LINE_LENGTH 160
        MAPPING_FILE ${PROJECT_SOURCE_DIR}/cmake/iwyu/morpheus.imp
    )
endif()
