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

    message(STATUS "Morpheus Generator: ${CMAKE_GENERATOR}") #debug
    message(STATUS "Morpheus: CCache found: ${CCACHE_BIN}. Enabling ccache as compiler cache tool.")
    if(${CMAKE_GENERATOR} MATCHES "Ninja|Makefiles")
        message(STATUS "found generator Ninja|Makefiles") #debug
        foreach(lang IN ITEMS ${MORPHEUS_LANGUAGES})
            set(CMAKE_${lang}_COMPILER_LAUNCHER ${CCACHE_BIN})
        endforeach()
    elseif(${CMAKE_GENERATOR} STREQUAL "Xcode")
        message(STATUS "found generator Xcode") #debug
        foreach(lang IN ITEMS ${MORPHEUS_LANGUAGES})
            set(launch${lang} ${CMAKE_BINARY_DIR}/launch-${lang})
            file(WRITE ${launch${lang}}
                "#!/bin/bash\n\n"
                "exec \"${CCACHE_BIN}\" \"${CMAKE_${lang}_COMPILER}\" \"$@\"\n"
            )
            execute_process(COMMAND chmod a+rx ${launch${lang}})
            set(${CMAKE_XCODE_ATTRIBUTE_${lang}} ${launch${lang}})
            if(lang STREQUAL "C")
                set(CMAKE_XCODE_ATTRIBUTE_LD ${launchC}) 
            elseif(lang STREQUAL "CXX")
                set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS ${launchCXX})
            endif()
        endforeach()
    elseif(${CMAKE_GENERATOR} MATCHES "Visual Studio")
        message(STATUS "found generator Visual Studio") #debug
        cmake_path(NATIVE_PATH CCACHE_BIN ccache_exe)
        file(WRITE ${CMAKE_BINARY_DIR}/launch-cl.cmd
        "@echo off\n"
        "\"${ccache_exe}\" \"${CMAKE_C_COMPILER}\" %*\n"
        )
        list(FILTER CMAKE_VS_GLOBALS EXCLUDE
            REGEX "^(CLTool(Path|Exe)|TrackFileAccess)=.*$"
        )
        list(APPEND CMAKE_VS_GLOBALS
            CLToolPath=${CMAKE_BINARY_DIR}
            CLToolExe=launch-cl.cmd
            TrackFileAccess=false
        )
    endif()
endfunction()
