morpheus_add_tests(
    NAME MorpheusGfxMetalTests
    FOLDER "Libraries/Gfx/Metal"
)

target_link_libraries(MorpheusGfxMetalTests
    PRIVATE
        morpheus::gfx::metal
)

target_sources(MorpheusGfxMetalTests
    PRIVATE
        adapter.tests.cpp
        concept_checks.tests.cpp
        render_system.tests.cpp
        video_mode.tests.cpp
)

set_target_properties(MorpheusGfxMetalTests
    PROPERTIES
        CMAKE_OBJCXX_STANDARD 20
        CMAKE_OBJCXX_STANDARD_REQUIRED ON
        CMAKE_OBJCXX_EXTENSIONS OFF
)
