morpheus_add_executable(
    NAME MacOSWindow
    FOLDER "Libraries/Gfx/Metal/Examples"
)

target_include_directories(MacOSWindow
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MacOSWindow
    PRIVATE
        morpheus::gfx::platform
        "-framework Foundation"
        "-framework Cocoa"
)

target_sources(MacOSWindow
    PRIVATE
        main.mm
)