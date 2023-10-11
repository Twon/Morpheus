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


#[=======================================================================[.rst:
enable_ccacche
------------------

Overview
^^^^^^^^

Enable use of Ccache for compiler caching during the build process.

.. code-block:: cmake

  enable_ccacche(
      [QUIET]
  )
   -- Searches for the ccache executable, and if found enables it for supported
   language with specified options.

  ``QUIET`` Silent output from this method.

#]=======================================================================]
function(enable_ccache)
    set(options QUIET)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(CCACHE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    find_program(CCACHE_BIN ccache REQUIRED)
    if(NOT CCACHE_BIN)
        message(STATUS "Morpheus: CCache not found. Rebuilding all the source files.")
        message(DEBUG "Morpheus: If CCache compiler cache is desired then ensure this is a supported platform and ensure the Conan buildenv is active")
        return()
    endif()

    message(STATUS "Morpheus: CCache found: ${CCACHE_BIN}. Enabling ccache as compiler cache tool.")
    foreach(lang IN ITEMS ${MORPHEUS_LANGUAGES})
        set(CMAKE_${lang}_COMPILER_LAUNCHER ${CCACHE_BIN})
    endforeach()
endfunction()
