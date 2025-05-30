#[[
Copyright 2025 Antony Peacock

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

function(enable_externis)
    set(options QUIET)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(EXTERNIS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "Externis is a GCC plugin, so use of this extension required the GCC compiler for C++ (CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID})")
    endif()

    set(EXTERNIS_DIR ${CMAKE_BINARY_DIR}/externis)
    set(EXTERNIS_SOURCE_DIR ${EXTERNIS_DIR})
    set(EXTERNIS_BUILD_DIR ${EXTERNIS_DIR}/build)
    find_program(GIT_EXECUTABLE git REQUIRED)
    file(REMOVE_RECURSE ${EXTERNIS_SOURCE_DIR})
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone -b main https://github.com/royjacobson/externis.git  "${EXTERNIS_SOURCE_DIR}"
        COMMAND_ERROR_IS_FATAL ANY
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -B${EXTERNIS_BUILD_DIR} -S${EXTERNIS_SOURCE_DIR} -DCMAKE_BUILD_TYPE=Release
        COMMAND_ERROR_IS_FATAL ANY
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${EXTERNIS_BUILD_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
    set(EXTERNIS_BINARY_PATH ${EXTERNIS_BUILD_DIR}/externis.so)
    if (NOT EXISTS ${EXTERNIS_BINARY_PATH})
        message(FATAL_ERROR "Externis was expected to be built at ${EXTERNIS_SO_PATH}")
    endif()
    if (NOT EXTERNIS_QUIET)
        message(STATUS "EXTERNIS: Shared object file at ${EXTERNIS_BINARY_PATH}")
    endif()
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/externis_reports)
    add_compile_options(-fplugin=${EXTERNIS_BINARY_PATH} -fplugin-arg-externis-trace-dir=${CMAKE_BINARY_DIR}/externis_reports)
endfunction()