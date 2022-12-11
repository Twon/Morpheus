include_guard(GLOBAL)

include(morpheus_add_target)

#[=======================================================================[.rst:
morpheus_add_library
------------------

Overview
^^^^^^^^

Project wrapper around add library which groups commonly associates patterns
and allows configuration for common optional settings

.. code-block:: cmake

  morpheus_add_library(
      [NAME <name>]
      [ALIAS <alias>]
      [FOLDER <folder>]
      [INTERFACE]
  )
   -- Generates library targets with default build directories and install options. 

  ``NAME``
    The ``NAME`` option is required to provide the internal name for the library.

  ``ALIAS``
    The ``ALIAS`` option is required to provide the external name for the library.

  ``FOLDER``
    The ``FOLDER`` option provides a folder location for the target within an IDE.

#]=======================================================================]
function(morpheus_add_library)
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

    morpheus_add_target(
        TYPE library
        NAME ${MORPHEUS_NAME}
        ALIAS ${MORPHEUS_ALIAS}
        FOLDER ${MORPHEUS_FOLDER}
    )

endfunction()