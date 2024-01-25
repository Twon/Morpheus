morpheus_add_tests(
    NAME MorpheusGfxTests
    FOLDER "Libraries/Gfx"
)

target_sources(MorpheusGfxTests
    PRIVATE
        image.tests.cpp
)

target_link_libraries(MorpheusGfxTests
    PRIVATE
        morpheus::gfx::platform
)

if (WIN32)
    add_subdirectory(win32)
endif(WIN32)
