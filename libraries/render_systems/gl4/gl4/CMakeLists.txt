find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if (NOT ${OPENGL_FOUND})

    message("OpenGL not found on the system.  Unable to support OpenGL based render system.")

else()

    add_library(MorpheusRenderSystemGL4 "")
    add_executable(MorpheusRenderSystemGL4Tests "")

    if (WIN32)
    #    add_subdirectory(wgl)
    endif(WIN32)

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

    target_link_libraries(MorpheusRenderSystemGL4
        PRIVATE
            MorpheusCore
            OpenGL::GL
    )

    get_target_property(SOURCES_FILES MorpheusRenderSystemGL4 SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

    target_sources(MorpheusRenderSystemGL4Tests
        PRIVATE
            gl4_render_system.tests.cpp
    )

    target_include_directories(MorpheusRenderSystemGL4Tests
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemGL4Tests
        PRIVATE
            MorpheusCore
            Catch2::Catch2

    )

    set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Tests
        PROPERTIES
            FOLDER "Libraries/RenderSystems/GL4"
    )

    set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Tests
        PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS TRUE
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemGL4Tests SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})

    install (TARGETS MorpheusRenderSystemGL4
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )
    
    add_test(
       NAME MorpheusRenderSystemGL4Tests
       COMMAND MorpheusRenderSystemGL4Tests
       WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    catch_discover_tests(MorpheusRenderSystemGL4Tests)
    add_coverage(MorpheusRenderSystemGL4)
    add_coverage(MorpheusRenderSystemGL4Tests)
endif()
