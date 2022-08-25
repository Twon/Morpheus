find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(glbinding REQUIRED glbinding glbinding-aux)

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
        ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(MorpheusRenderSystemGL4
    PRIVATE
        MorpheusCore
        OpenGL::GL
        GLEW::GLEW
        glbinding::glbinding
)

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
        MorpheusRenderSystemGL4
        Catch2::Catch2
)

set_target_properties(MorpheusRenderSystemGL4 MorpheusRenderSystemGL4Tests
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        FOLDER Libraries/RenderSystems/GL4
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

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
