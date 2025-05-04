morpheus_add_tests(
    NAME MorpheusGfxTests
    FOLDER "Libraries/Gfx"
)

target_sources(MorpheusGfxTests
    PRIVATE
        image.tests.cpp
        monitor.tests.cpp
        render_window.tests.cpp
        vendor.tests.cpp
)

target_link_libraries(MorpheusGfxTests
    PRIVATE
        morpheus::gfx::platform
)

if (WIN32)
    add_subdirectory(win32)
endif(WIN32)

if(UNIX AND NOT APPLE)
    add_subdirectory(x11)
endif(UNIX AND NOT APPLE)
