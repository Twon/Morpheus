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

if(MORPHEUS_BUILD_DOCUMENTATION)
    find_package(Doxygen)

    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    # If using Conan find modules to find an installed Doxygen then we lose doxygen_add_docs, 
    # so include the find module directly to access this method as a work around.
    include(${CMAKE_ROOT}/Modules/FindDoxygen.cmake)

    list(APPEND DOXYGEN_EXCLUDE_PATTERNS
        "${CMAKE_CURRENT_BINARY_DIR}/_deps/*"
        "*/thirdparty/*"
        "*/tests/*"
    )

#[[
    FetchContent_Declare(doxygen_theme URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.0.2.zip)
    FetchContent_MakeAvailable(doxygen_theme)
    list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET
        "${doxygen_theme_SOURCE_DIR}/doxygen-awesome.css"
        "${doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css"
    )

    set(DOXYGEN_GENERATE_TREEVIEW YES)
]]
    set(DOXYGEN_HTML_OUTPUT ${CMAKE_BINARY_DIR}/documentation/doxygen)

    file(MAKE_DIRECTORY ${DOXYGEN_HTML_OUTPUT})

    doxygen_add_docs(Doxygen
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libraries/
        COMMENT "Generating API documentation with Doxygen"
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
        COMMAND ${documentationSphinx} ${DOXYGEN_HTML_OUTPUT} ${CMAKE_BINARY_DIR}/documentation/sphinx
        DEPENDS ${documentationSphinx}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with Sphinx"
    )
    set_target_properties(Documentation PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})

    install(DIRECTORY ${sphinxOutput} DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()