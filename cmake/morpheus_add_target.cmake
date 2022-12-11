include_guard(GLOBAL)


#[=======================================================================[.rst:
morpheus_add_target
------------------

Overview
^^^^^^^^

Helper function for internal use when creating targets. Ensures targets receive
commonly associated attributes.

.. code-block:: cmake

  morpheus_add_library(
      [TYPE <library|executable>]
      [NAME <name>]
      [ALIAS <alias>]
      [FOLDER <folder>]
      [INTERFACE]
  )
   -- Generates targets with default build directories and install options. 

  ``TYPE``
    The ``TYPE`` option is required to provide the type of target to create.

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` option is required to provide the external name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

  ``INTERFACE``
    The ``INTERFACE`` option is only applicable for library targets and specifies
    the library is an interface library.

#]=======================================================================]
function(morpheus_add_target)
    set(options INFERFACE)
    set(oneValueArgs TYPE NAME ALIAS FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT MORPHEUS_TYPE)
        message(FATAL_ERROR "TYPE parameter must be supplied")
    else()
        set(VALID_TARGET_TYPES library executable)
        list(FIND VALID_TARGET_TYPES ${MORPHEUS_TYPE} index)
        if(index EQUAL -1)
            message(FATAL_ERROR "TYPE must be one of <${VALID_TARGET_TYPES}>")
        endif()
    endif()
    if (NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()
    if (NOT MORPHEUS_ALIAS AND MORPHEUS_TYPE STREQUAL library)
        message(FATAL_ERROR "ALIAS parameter must be supplied for library targets")
    endif()
    if (NOT MORPHEUS_INFERFACE AND NOT MORPHEUS_TYPE STREQUAL library)
        message(FATAL_ERROR "INFERFACE parameter can only be used with library targets")
    endif()

    if (MORPHEUS_TYPE STREQUAL executable)
        add_executable(${MORPHEUS_NAME})
        if (MORPHEUS_ALIAS)
            add_executable(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
        endif()
    else()
        if (NOT MORPHEUS_INFERFACE)
            add_library(${MORPHEUS_NAME})
        else()
            add_library(${MORPHEUS_NAME} INTERFACE)
        endif()
        add_library(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
    endif()

    morpheus_add_target_properties(
        NAME ${MORPHEUS_NAME}
        FOLDER ${MORPHEUS_FOLDER}
    )
endfunction()

#[=======================================================================[.rst:
morpheus_add_target_properties
------------------

Overview
^^^^^^^^

Helper function for internal use when creating targets. Ensures targets receive
commonly associated attributes.

.. code-block:: cmake

  morpheus_add_target_properties(
      [NAME <name>]
      [FOLDER <folder>]
  )
   -- Generates targets with default build directories and install options. 

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

#]=======================================================================]
function(morpheus_add_target_properties)
    set(options)
    set(oneValueArgs NAME FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

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
