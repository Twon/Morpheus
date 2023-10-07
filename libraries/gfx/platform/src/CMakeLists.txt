morpheus_add_library(
    NAME MorpheusGfxPlatform
    ALIAS morpheus::gfx::platform
    FOLDER "Libraries/Gfx/Platform"
)

target_include_directories(MorpheusGfxPlatform
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxPlatform
	PUBLIC
		morpheus::core
)

set_target_properties(MorpheusGfxPlatform
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/platform)
