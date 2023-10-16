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
    set(multiValueArgs LANGUAGES OPTIONS)
    cmake_parse_arguments(CCACHE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (CCACHE_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Morpheus: enable_ccache invalid arguments ${CCACHE_UNPARSED_ARGUMENTS}")
    endif()
    
    find_program(CCACHE_BIN ccache)
    if (NOT CCACHE_BIN)
        message(STATUS "Morpheus: CCache not found. Rebuilding all the source files.")
        message(DEBUG "Morpheus: If CCache compiler cache is desired then ensure this is a supported platform and ensure the Conan buildenv is active")
        return()
    endif()
    message(STATUS "Morpheus: CCache found: ${CCACHE_BIN}. Enabling ccache as compiler cache tool.")

    if (CCACHE_DEBUG)
        message(STATUS "Morpheus: Create CCache debug files")
        list(APPEND ccacheEnv "CCACHE_DEBUG=1")
    endif()
    if (CCACHE_ICECC)
        find_program(ICECC_BIN icecc)
        if (ICECC_BIN)
            message(STATUS "Morpheus: build with Icecream ${ICECC_BIN}")
            list(APPEND ccacheEnv "CCACHE_PREFIX=icecc")
        endif()
    endif()
    if (CCACHE_SLOPPINESS)
        message(STATUS "Morpheus: Enable CCache sloppiness")
        list(APPEND ccacheEnv "CCACHE_SLOPPINESS=pch_defines,time_macros")
    endif()
    string(REPLACE ";" " " ccacheEnvString "${ccacheEnv}")

    if (${CMAKE_GENERATOR} MATCHES "Ninja|Makefiles")
        message(STATUS "Morpheus: found generator Ninja|Makefiles")
        foreach(lang IN ITEMS ${LANGUAGES})
            set(CMAKE_${lang}_COMPILER_LAUNCHER
                ${CMAKE_COMMAND} -E env ${ccacheEnvString} ${CCACHE_BIN})
        endforeach()
    elseif (${CMAKE_GENERATOR} STREQUAL "Xcode")
        message(STATUS "Morpheus: found generator Xcode")
        foreach(lang IN ITEMS ${LANGUAGES})
            set(launch${lang} ${CMAKE_BINARY_DIR}/launch-${lang})
            file(WRITE ${launch${lang}} "#!/bin/bash\n\n")
            foreach(envVal IN ITEMS ${ccacheEnv})
                file(APPEND ${launch${lang}} "export ${envVal}\n")
            endforeach() 
            file(APPEND ${launch${lang}} "exec \"${CCACHE_BIN}\" \"${CMAKE_${lang}_COMPILER}\" \"$@\"\n")     
            execute_process(COMMAND chmod a+rx ${launch${lang}})
            set(${CMAKE_XCODE_ATTRIBUTE_${lang}} ${launch${lang}})
            if(lang STREQUAL "C")
                set(CMAKE_XCODE_ATTRIBUTE_LD ${launchC}) 
            elseif(lang STREQUAL "CXX")
                set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS ${launchCXX})
            endif()
        endforeach()
    elseif (${CMAKE_GENERATOR} MATCHES "Visual Studio" and 
           (${LANGUAGES} STREQUAL "C" or 
            ${LANGUAGES} STREQUAL "CXX" or
            ${LANGUAGES} STREQUAL "CUDA"))
        message(STATUS "Morpheus: found generator Visual Studio")
        cmake_path(NATIVE_PATH CCACHE_BIN ccache_exe)
        file(WRITE ${CMAKE_BINARY_DIR}/launch-cl.cmd "@echo off\n")
        foreach(envVal IN ITEMS ${ccacheEnv})
            file(APPEND ${CMAKE_BINARY_DIR}/launch-cl.cmd "set ${envVal}\n")
        endforeach()
        file(APPEND ${CMAKE_BINARY_DIR}/launch-cl.cmd "\"${ccache_exe}\" \"${CMAKE_C_COMPILER}\" %*\n")
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
