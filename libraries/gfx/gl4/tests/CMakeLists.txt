morpheus_add_tests(
    NAME MorpheusGfxGL4Tests
    FOLDER "Libraries/Gfx/GL4"
    LABELS GPU
)

target_link_libraries(MorpheusGfxGL4Tests
    PRIVATE
        morpheus::gfx::gl4
)

target_sources(MorpheusGfxGL4Tests
    PRIVATE
        concept_checks.tests.cpp
        render_system.tests.cpp
)

if (WIN32)
    add_subdirectory(wgl)
endif(WIN32)

if(UNIX AND NOT APPLE)
    add_subdirectory(xgl)
endif(UNIX AND NOT APPLE)
