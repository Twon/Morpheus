include_guard()


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
    set(options)
    set(oneValueArgs NAME ALIAS FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()
    if (NOT MORPHEUS_ALIAS)
        message(FATAL_ERROR "ALIAS parameter must be supplied")
    endif()
    add_library(${MORPHEUS_NAME})
    add_library(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})

    target_link_libraries(${MORPHEUS_NAME}
        PRIVATE
             Catch2::Catch2
             GTest::gmock
    )

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