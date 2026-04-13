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

include(IDESettings)
include(virtualenv)

option(MORPHEUS_BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)


macro(cmake_to_doxyfile_string string)
    string (REPLACE ";" " " ${string} "${${string}}")
endmacro()

function(add_documentation)
    set(options)
    set(oneValueArgs PROJECT PROJECT_NUMBER OUTPUT_DIRECTORY WORKING_DIRECTORY)
    set(multiValueArgs INPUT_DIRECTORY PUBLIC_HEADERS)
    cmake_parse_arguments(DOCUMENTATION "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (DOCUMENTATION_PROJECT)
        set(DOXYGEN_PROJECT ${DOCUMENTATION_PROJECT})
    endif()
    if (DOCUMENTATION_PROJECT_NUMBER)
        set(DOXYGEN_PROJECT_NUMBER ${DOCUMENTATION_PROJECT_NUMBER})
    endif()
    if (NOT DOCUMENTATION_INPUT_DIRECTORY)
        set(DOXYGEN_INPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
    else()
        foreach(input ${DOCUMENTATION_INPUT_DIRECTORY})
            if(NOT EXISTS "${input}")
                message(SEND_ERROR "${input} does not exist on disk.")
            endif()
        endforeach()

        set(DOXYGEN_INPUT_DIRECTORY ${DOCUMENTATION_INPUT_DIRECTORY})
        cmake_to_doxyfile_string(DOXYGEN_INPUT_DIRECTORY)
    endif()
    if (NOT DOCUMENTATION_OUTPUT_DIRECTORY)
        set(DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/documentation)
    endif()
    if (NOT DOCUMENTATION_WORKING_DIRECTORY)
        message(FATAL_ERROR "WORKING_DIRECTORY parameter must be supplied")
    endif()

    find_package(Doxygen REQUIRED)

    # If using Conan find modules to find an installed Doxygen then we lose doxygen_add_docs,
    # so include the find module directly to access this method as a work around.
    include(${CMAKE_ROOT}/Modules/FindDoxygen.cmake)

    list(APPEND DOXYGEN_EXCLUDE_PATTERNS
        "*/.git/*"
        "*/CMakeFiles/*"
        "*/_CPack_Packages/*"
        "${CMAKE_CURRENT_BINARY_DIR}/*"
        "*/_deps/*"
        "*/thirdparty/*"
        "*/tests/*"
    )
    cmake_to_doxyfile_string(DOXYGEN_EXCLUDE_PATTERNS)

    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_OUTPUT_DIRECTORY ${DOCUMENTATION_OUTPUT_DIRECTORY}/doxygen)
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_GENERATE_XML YES)
    set(DOXYGEN_XML_OUTPUT xml)

    configure_file(${PROJECT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    set(doxygenXmlOutputDir ${DOXYGEN_OUTPUT_DIRECTORY}/${DOXYGEN_XML_OUTPUT})
    set(doxygenIndex "${doxygenXmlOutputDir}/index.xml")

    add_custom_command(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIRECTORY}
        COMMAND Doxygen::doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        OUTPUT ${doxygenIndex}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${DOCUMENTATION_PUBLIC_HEADERS}
        WORKING_DIRECTORY ${DOCUMENTATION_WORKING_DIRECTORY}
        COMMENT "Generating API documentation with Doxygen"
    )

    add_custom_target( Doxygen
        DEPENDS ${doxygenIndex}
        COMMENT "Checking if Doxygen XML re-generation is required"
    )

    set_target_properties(Doxygen PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})

    set(documentationVenv ${CMAKE_BINARY_DIR}/.venv/documentation)
    set(documentationSphinx ${documentationVenv}/bin/sphinx-build)

    virtualenv_create(
        DESTINATION ${documentationVenv}
        REQUIREMENTS ${PROJECT_SOURCE_DIR}/cmake/requirements/documentation_requirements.txt
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        OUTPUT
            ${documentationSphinx}
    )

    set(sphinxOutput ${CMAKE_BINARY_DIR}/documentation/sphinx)
    add_custom_target(Documentation
        COMMAND ${documentationSphinx} "-Dbreathe_projects.morpheus=${doxygenXmlOutputDir}"
                ${PROJECT_SOURCE_DIR}/docs ${DOCUMENTATION_OUTPUT_DIRECTORY}/sphinx
        DEPENDS ${documentationSphinx} ${doxygenIndex} Doxygen
        WORKING_DIRECTORY ${DOCUMENTATION_WORKING_DIRECTORY}
        COMMENT "Generating documentation with Sphinx"
    )
    set_target_properties(Documentation PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})

    install(DIRECTORY ${sphinxOutput} DESTINATION ${CMAKE_INSTALL_DOCDIR})

endfunction()


if(MORPHEUS_BUILD_DOCUMENTATION)
    file(GLOB_RECURSE publicHeaders "${PROJECT_SOURCE_DIR}/libraries/*.hpp")
    add_documentation(
        PROJECT Morpheus
        PROJECT_NUMBER ${MORPHEUS_VERSION}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        PUBLIC_HEADERS ${publicHeaders}
        INPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/examples
        INPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libraries
        OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/documentation
    )
endif()
