find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if (NOT ${OPENGL_FOUND})
    message("OpenGL not found on the system.  Unable to support OpenGL based render system.")
    return()
endif()

add_library(MorpheusRenderSystemGL4 "")
add_executable(MorpheusRenderSystemGL4Tests "")

target_sources(MorpheusRenderSystemGL4
    PUBLIC
        render_system.hpp
        type_mapping.hpp
    PRIVATE
        render_system.cpp
        type_mapping.cpp
)

if (WIN32)
    add_subdirectory(wgl)
endif(WIN32)

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
        render_system.tests.cpp
)

target_include_directories(MorpheusRenderSystemGL4Tests
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(MorpheusRenderSystemGL4Tests
    PRIVATE
        MorpheusCore
        Catch2::Catch2
)

set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Tests
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        FOLDER "Libraries/RenderSystems/GL4"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemGL4Tests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})

install(TARGETS MorpheusRenderSystemGL4
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_test(
    NAME MorpheusRenderSystemGL4Tests
    COMMAND MorpheusRenderSystemGL4Tests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
catch_discover_tests(MorpheusRenderSystemGL4Tests)
add_coverage(MorpheusRenderSystemGL4)
add_coverage(MorpheusRenderSystemGL4Tests)
