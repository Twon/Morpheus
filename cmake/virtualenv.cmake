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

find_package(Python3 REQUIRED COMPONENTS Interpreter)

#[=======================================================================[.rst:
virtualenv_create
------------------

Overview
^^^^^^^^

Creates a Python virtual environment for use with a specific set of requirements
within the build stage.

.. code-block:: cmake

  virtualenv_create(
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
    virtualenv_create(
        DESTINATION ${pyenv}
        REQUIREMENTS requirements.txt
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT module.py
    )
    add_custom_command(
        COMMAND ${pyenv}/bin/python some/script.py
        DEPENDS ${pyenv}/bin/python
        OUTPUT ...
    )

#]=======================================================================]
function(virtualenv_create)
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
