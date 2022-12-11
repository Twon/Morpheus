include_guard(GLOBAL)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

#[=======================================================================[.rst:
create_python_virtualenv
------------------

Overview
^^^^^^^^

Creates a Python virtual environment for use with a specific set of requirements 
within the build stage.

.. code-block:: cmake

  create_python_virtualenv(
      [QUIET]
      [DESTINATION <folder>]
      [REQUIREMENTS <requirements>]
      [OUTPUT <out files>]
      [WORKING_DIRECTORY <directory>]
      [EXTRA_ARGS <args>]
  )

When using the virtialemv as a dependency in a custom target then make sure to depend 
on the python executable ${envdir}/bin/python to ensure that the setup command is run first.

Example
^^^^^^^

.. code-block:: cmake

    set(pyenv ${CMAKE_CURRENT_BINARY_DIR}/pyenv)
    mmb_create_python_virtualenv(
        DESTINATION ${pyenv}
        EXTRA_ARGS
            COMMAND ${pyenv}/bin/python -m pip install -r requirements.txt
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    add_custom_command(
        COMMAND ${pyenv}/bin/python some/script.py
        DEPENDS ${pyenv}/bin/python
        OUTPUT ...
    )

#]=======================================================================]
function(create_python_virtualenv)
    set(options)
    set(oneValueArgs DESTINATION REQUIREMENTS WORKING_DIRECTORY)
    set(multiValueArgs OUTPUT EXTRA_ARGS)

    cmake_parse_arguments(PYTHON_VENV "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT PYTHON_VENV_DESTINATION)
        message(FATAL_ERROR "DESTINATION parameter must be supplied")
    endif()

    if (NOT PYTHON_VENV_REQUIREMENTS)
        message(FATAL_ERROR "REQUIREMENTS parameter must be supplied")
    endif()

    if (NOT PYTHON_VENV_WORKING_DIRECTORY)
        message(FATAL_ERROR "WORKING_DIRECTORY parameter must be supplied")
    endif()

    if (NOT EXISTS ${PYTHON_VENV_REQUIREMENTS})
        message(FATAL_ERROR "REQUIREMENTS must exist, invalid path: ${PYTHON_VENV_REQUIREMENTS}")
    endif()

    set(PYTHON_VENV_INTERPRETER ${PYTHON_VENV_DESTINATION}/bin/python)

    add_custom_command(
        OUTPUT ${PYTHON_VENV_INTERPRETER}
        COMMAND ${Python3_EXECUTABLE} -m venv ${PYTHON_VENV_DESTINATION}
        COMMAND ${PYTHON_VENV_INTERPRETER} -m pip install --upgrade pip
        COMMAND  ${PYTHON_VENV_INTERPRETER} -m pip install -r ${PYTHON_VENV_REQUIREMENTS}
        WORKING_DIRECTORY ${PYTHON_VENV_WORKING_DIRECTORY}
        OUTPUT ${PYTHON_VENV_OUTPUT}
        ${PYTHON_VENV_EXTRA_ARGS}
    )

endfunction()
