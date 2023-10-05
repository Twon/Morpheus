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

if (${MORPHEUS_ENABLE_MOLD})
    find_program(MOLD_BIN mold REQUIRED)
    if(MOLD_BIN)
        message(STATUS "Morpheus: Mold linker found: ${MOLD_BIN}.  Enabling mold as active linker.")
        target_link_options(MorpheusConfig
            INTERFACE
                "-fuse-ld=mold"
        )
    else()
        message(STATUS "Morpheus: Mold linker not found.  Reverting to default linker.")
        message(DEBUG "Morpheus: If Mold linker is desired then ensure this is a supported platform and ensure the Conan buildenv is active")
    endif()
endif()
