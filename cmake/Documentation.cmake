include(IDESettings)

find_package(Doxygen)
option(MORPHEUS_BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(MORPHEUS_BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    doxygen_add_docs(Documentation
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libraries/
        COMMENT "Generating API documentation with Doxygen"
    )

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION documentation)

    set_target_properties(Documentation PROPERTIES FOLDER ${MORPHEUS_PREDEFINED_TARGETS})
endif()