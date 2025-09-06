find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glbinding REQUIRED glbinding glbinding-aux)
find_package(khrplatform REQUIRED)

if (NOT ${OPENGL_FOUND})
    message("OpenGL not found on the system.  Unable to support OpenGL based render system.")
    return()
endif()

morpheus_add_library(
    NAME MorpheusGfxGL4
    ALIAS morpheus::gfx::gl4
    FOLDER "Libraries/Gfx/GL4"
)

target_include_directories(MorpheusGfxGL4
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxGL4
    PUBLIC
        morpheus::gfx::platform
        OpenGL::GL
        GLEW::GLEW
        glbinding::glbinding
        khrplatform::khrplatform
)

set_target_properties(MorpheusGfxGL4
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/gl4)
