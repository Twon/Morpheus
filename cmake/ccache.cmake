#[[
Copyright 2022 Antony Peacock

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
enable_ccache
------------------

Overview
^^^^^^^^

Locates and enable ccache during compilation.

.. code-block:: cmake

  enable_ccache(
      [QUIET]
  )
   -- Call the include what you use for each file as the project builds.

  ``QUIET`` Silence tracing output.

#]=======================================================================]
function(enable_ccache)
    set(options QUIET REQUIRED)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(CCACHE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
    
    find_program(IWYU_PATH iwyu)
    if (NOT IWYU_PATH)
        message(STATUS "iwyu: include-what-you-use not found, disabling support.")
        return()
    endif()

    set(CMAKE_C_INCLUDE_WHAT_YOU_USE "${IWYU_PATH};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-transitive_includes_only;" PARENT_SCOPE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_PATH};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-transitive_includes_only" PARENT_SCOPE)

    if (NOT IWYU_QUIET)
        message(STATUS "iwyu: include-what-you-use found, enabling support (via ${CMAKE_CXX_INCLUDE_WHAT_YOU_USE}).")
    endif()

#    set_target_properties(MorpheusCore PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${IWYU_PATH};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-transitive_includes_only")
endfunction()