find_package(OpenGL)

if (NOT ${OPENGL_FOUND})

    message("OpenGL not found on the system.  Unable to support OpenGL based render system.")

else()

    add_library(MorpheusRenderSystemGL4 "")
    target_sources(MorpheusRenderSystemGL4
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/gl4_render_system.hpp"
            "${CMAKE_CURRENT_LIST_DIR}/gl4_render_system.cpp"
    )

    target_compile_definitions(MorpheusRenderSystemGL4
        PUBLIC
            MORPHEUS_SHARED_BUILD=1
    )

    target_include_directories(MorpheusRenderSystemGL4
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemGL4
        PRIVATE
            MorpheusCore
    )

    set_target_properties(MorpheusRenderSystemGL4
        PROPERTIES
            FOLDER "Libraries/RenderSystems"
    )

    set_target_properties(MorpheusRenderSystemGL4
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    install (TARGETS MorpheusRenderSystemGL4
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )
endif()

