#[[
Copyright 2024 Antony Peacock

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

#[=======================================================================[.rst:
morpheus_conformance_check
------------------

Overview
^^^^^^^^

Checks for the given compiler supported version of a package if the fallback package
is required.

.. code-block:: cmake

  morpheus_conformance_check(
      [RESULT <result>]
      [MSVC_VERSION <msvc version>]
      [GCC_VERSION <gcc version>]
      [CLANG_VERSION <clang version>]
      [APPLE_CLANG_VERSION <apple-clang version>]
  )
   -- Generates library targets with default build directories and install options.

  ``RESULT``
    The ``RESULT`` option is required to store the results of the function.

  ``MSVC_VERSION``
    The ``MSVC_VERSION`` option is requests a version check against MSVC version
    if it is the active compiler.

  ``GCC_VERSION``
    The ``GCC_VERSION`` option is requests a version check against GCC version
    if it is the active compiler.

  ``CLANG_VERSION``
    The ``CLANG_VERSION`` option is requests a version check against Clang version
    if it is the active compiler.

  ``APPLE_CLANG_VERSION``
    The ``APPLE_CLANG_VERSION`` option is requests a version check against
    apple-clang if it is the active compiler.


#]=======================================================================]
function(morpheus_conformance_check)
    set(options)
    set(oneValueArgs RESULT MSVC_VERSION GCC_VERSION CLANG_VERSION APPLE_CLANG_VERSION)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (NOT MORPHEUS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()
    if (NOT MORPHEUS_MSVC_VERSION AND NOT MORPHEUS_GCC_VERSION AND NOT MORPHEUS_CLANG_VERSION AND NOT MORPHEUS_APPLE_CLANG_VERSION)
        message(FATAL_ERROR "Must check a minumum of one compiler version")
    endif()

    if (MORPHEUS_MSVC_VERSION AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${MORPHEUS_MSVC_VERSION})
        set(${MORPHEUS_RESULT} TRUE PARENT_SCOPE)
    elseif (MORPHEUS_GCC_VERSION AND CMAKE_CXX_COMPILER_ID STREQUAL "GNUC" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${MORPHEUS_MSVC_VERSION})
        set(${MORPHEUS_RESULT} TRUE PARENT_SCOPE)
    elseif (MORPHEUS_CLANG_VERSION AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${MORPHEUS_MSVC_VERSION})
        set(${MORPHEUS_RESULT} TRUE PARENT_SCOPE)
    elseif (MORPHEUS_APPLE_CLANG_VERSION AND CMAKE_CXX_COMPILER_ID STREQUAL "Apple-Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${MORPHEUS_MSVC_VERSION})
        set(${MORPHEUS_RESULT} TRUE PARENT_SCOPE)
    else()
        set(${MORPHEUS_RESULT} FALSE PARENT_SCOPE)
    endif()

endfunction()
