morpheus_add_testing_library(
    INFERFACE
	NAME MorpheusGfxPlatformMocking
	ALIAS morpheus::gfx::platform::mocking
    FOLDER "Libraries/Gfx/Platform"
)

target_include_directories(MorpheusGfxPlatformMocking
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MorpheusGfxPlatformMocking
    INTERFACE
        morpheus::gfx::platform
)

set_target_properties(MorpheusGfxPlatformMocking
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/platform)
