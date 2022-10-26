add_library(MorpheusGfxPlatform)
add_library(morpheus::gfx::platform ALIAS MorpheusGfxPlatform)
target_link_libraries(MorpheusGfxPlatform
	PUBLIC
		morpheus::core
)

add_subdirectory(morpheus/gfx/platform)