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
      [NO_INSTALL]
  )
   -- Generates targets with default build directories and install options.

  ``ALIAS``
    The ``ALIAS`` option is required to provide the external name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

  ``INTERFACE``
    The ``INTERFACE`` option is only applicable for library targets and specifies
    the library is an interface library.

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``NO_INSTALL``
    The ``NO_INSTALL`` option disables the target supporting the install step.

  ``TYPE``
    The ``TYPE`` option is required to provide the type of target to create.

#]=======================================================================]
function(morpheus_add_target)
    set(options NO_INSTALL INTERFACE)
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
    if (MORPHEUS_INTERFACE AND NOT MORPHEUS_TYPE STREQUAL library)
        message(FATAL_ERROR "INTERFACE parameter can only be used with library targets")
    endif()
    if(${MORPHEUS_INTERFACE})
        set(isInterface "INTERFACE")
    endif()
    if(${MORPHEUS_NO_INSTALL})
        set(noInstall "NO_INSTALL")
    endif()

    if (MORPHEUS_TYPE STREQUAL executable)
        add_executable(${MORPHEUS_NAME})
        if (MORPHEUS_ALIAS)
            add_executable(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
        endif()
    else()
        add_library(${MORPHEUS_NAME} ${isInterface})
        add_library(${MORPHEUS_ALIAS} ALIAS ${MORPHEUS_NAME})
    endif()

    morpheus_add_target_properties(
        NAME ${MORPHEUS_NAME}
        FOLDER ${MORPHEUS_FOLDER}
        ${isInterface}
        ${noInstall}
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

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

  ``INTERFACE``
    The ``INTERFACE`` option is only applicable for library targets and specifies
    the library is an interface library.

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``NO_INSTALL``
    The ``NO_INSTALL`` option disables the target supporting the install step.

#]=======================================================================]
function(morpheus_add_target_properties)
    set(options NO_INSTALL INTERFACE)
    set(oneValueArgs NAME FOLDER)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(${MORPHEUS_INTERFACE})
        set(scope "INTERFACE")
    else()
        set(scope "PUBLIC")
    endif()

    target_compile_features(${MORPHEUS_NAME} ${scope} cxx_std_23)

    set_target_properties(${MORPHEUS_NAME}
        PROPERTIES
            CXX_STANDARD 23
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
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

    # Create an empty header set here so that the subsequent install step finds it.
    target_sources(${MORPHEUS_NAME} ${scope} FILE_SET HEADERS FILES)

    if (NOT ${MORPHEUS_NO_INSTALL})
        install(TARGETS ${MORPHEUS_NAME}
                EXPORT morpheus-export-set
                FILE_SET HEADERS
                INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()
endfunction()
