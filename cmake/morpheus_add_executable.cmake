include_guard(GLOBAL)


#[=======================================================================[.rst:
morpheus_add_executable
------------------

Overview
^^^^^^^^

Project wrapper around add executable which groups commonly associates patterns
and allows configuration for common optional settings

.. code-block:: cmake

  morpheus_add_executable(
      [NAME <name>]
      [ALIAS <alias>]
      [FOLDER <folder>]
  )
   -- Generates library targets with default build directories and install options. 

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` option is required to provide the external name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

#]=======================================================================]
function(morpheus_add_executable)
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

    install(TARGETS ${MORPHEUS_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endfunction()