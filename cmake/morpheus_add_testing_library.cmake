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
morpheus_add_testing_library
------------------

Overview
^^^^^^^^

Project wrapper for creating a library containing common testing functionality to
be shared across test suites. Testing libraries will not be installed as part of
the installation process

.. code-block:: cmake

  morpheus_add_testing_library(
      [NAME <name>]
      [ALIAS <alias>]
      [FOLDER <folder>]
      [INTERFACE]
  )
   -- Generates a testing library targets with default build directories and 
   setting. 

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` option is required to provide the external name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

#]=======================================================================]
function(morpheus_add_testing_library)
    set(options INFERFACE)
    set(oneValueArgs NAME ALIAS FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()
    if (NOT MORPHEUS_ALIAS)
        message(FATAL_ERROR "ALIAS parameter must be supplied")
    endif()

    if (NOT MORPHEUS_INFERFACE)
        add_library(${MORPHEUS_NAME})
        target_link_libraries(${MORPHEUS_NAME}
            PUBLIC
                 Catch2::Catch2
                 GTest::gmock
        )
    else()
        add_library(${MORPHEUS_NAME} INTERFACE)
        target_link_libraries(${MORPHEUS_NAME}
            INTERFACE
                 Catch2::Catch2
                 GTest::gmock
        )
    endif()

    add_library(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})

    set_target_properties(${MORPHEUS_NAME}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    if (MORPHEUS_FOLDER)
        set_target_properties(${MORPHEUS_NAME}
            PROPERTIES
                FOLDER ${MORPHEUS_FOLDER}
        )
    endif()

endfunction()