include_guard()

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
  )
   -- Generates test executable targets with default build directories and settings. 

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` parameter can be optional provided to give the external name for 
    the test execcutable.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

#]=======================================================================]
function(morpheus_add_tests)
    set(options)
    set(oneValueArgs NAME ALIAS FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()
    
    add_executable(${MORPHEUS_NAME})
    if (MORPHEUS_ALIAS)
        add_executable(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
    endif()

    #find_package(Catch2 3 REQUIRED HINTS ${Catch2_DIR})
    target_link_libraries(${MORPHEUS_NAME}
        PRIVATE
             Catch2::Catch2
             morpheus::core::testing
    )

    configure_file(${PROJECT_SOURCE_DIR}/libraries/core/testing/morpheus/catch2/main.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/main.cpp @ONLY)
    target_sources(${MORPHEUS_NAME}
        PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR}/main.cpp
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

    add_test(
        NAME ${MORPHEUS_NAME}
        COMMAND ${MORPHEUS_NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    include(Catch)
    catch_discover_tests(${MORPHEUS_NAME})
    #add_coverage(MorpheusCoreTests)

endfunction()