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

include(third_party)

#[=======================================================================[.rst:
morpheus_add_tests
------------------

Overview
^^^^^^^^

Project wrapper around add execcuable for test excuables which groups commonly
associates patterns and allows configuration for common optional settings

.. code-block:: cmake

  morpheus_add_tests(
      [NAME <name>]
      [ALIAS <alias>]
      [FOLDER <folder>]
      [LABELS <labels...>]
  )
   -- Generates test executable targets with default build directories and settings.

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` parameter can be optional provided to give the external name for
    the test execcutable.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

  ``LABELS``
    The ``LABELS`` option provides a list of labels to apply to the the test suite.

#]=======================================================================]
function(morpheus_add_tests)
    set(options)
    set(oneValueArgs NAME ALIAS FOLDER)
    set(multiValueArgs LABELS)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()

    add_executable(${MORPHEUS_NAME})
    if(MORPHEUS_ALIAS)
        add_executable(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
    endif()

    # find_package(Catch2 3 REQUIRED HINTS ${Catch2_DIR})
    target_link_libraries(${MORPHEUS_NAME} PRIVATE Catch2::Catch2 morpheus::core::testing)

    configure_file(
        ${PROJECT_SOURCE_DIR}/libraries/core/testing/morpheus/catch2/main.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/main.cpp
        @ONLY
    )
    target_sources(${MORPHEUS_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/main.cpp)

    set_target_properties(
        ${MORPHEUS_NAME}
        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    add_test(
        NAME ${MORPHEUS_NAME}
        COMMAND ${MORPHEUS_NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )

    if(MORPHEUS_FOLDER)
        set_target_properties(${MORPHEUS_NAME} PROPERTIES FOLDER ${MORPHEUS_FOLDER})
    endif()

    if(MORPHEUS_LABELS)
        set_property(TEST ${MORPHEUS_NAME} PROPERTY LABELS ${MORPHEUS_LABELS})
    endif()

    include(Catch)
    catch_discover_tests(${MORPHEUS_NAME} PROPERTIES LABELS ${MORPHEUS_LABELS})

endfunction()
