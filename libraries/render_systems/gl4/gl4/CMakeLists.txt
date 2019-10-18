find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if (NOT ${OPENGL_FOUND})

    message("OpenGL not found on the system.  Unable to support OpenGL based render system.")

else()

    add_library(MorpheusRenderSystemGL4 "")
    add_executable(MorpheusRenderSystemGL4Test "")

    add_subdirectory(wgl)

    target_sources(MorpheusRenderSystemGL4
        PRIVATE
            gl4_render_system.hpp
            gl4_render_system.cpp
            gl4_type_mapping.hpp
            gl4_type_mapping.cpp
    )

    #target_compile_definitions(MorpheusRenderSystemGL4
    #    PUBLIC
    #        MORPHEUS_SHARED_BUILD=1
    #)

    target_include_directories(MorpheusRenderSystemGL4
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_include_directories(MorpheusRenderSystemGL4Test
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemGL4
        PRIVATE
            MorpheusCore
            OpenGL::GL
    )

    target_link_libraries(MorpheusRenderSystemGL4Test
        PRIVATE
            MorpheusCore
            catch2::catch2
    )

    set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Test
        PROPERTIES
            FOLDER "Libraries/RenderSystems/GL4"
    )

    set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Test
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    get_target_property(SOURCES_FILES MorpheusRenderSystemGL4 SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

    get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemGL4Test SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})

    target_sources(MorpheusRenderSystemGL4Test
        PRIVATE
            ${SOURCES_FILES}
    )

    install (TARGETS MorpheusRenderSystemGL4
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )
endif()
