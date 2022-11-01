morpheus_add_library(
    NAME MorpheusGfxIntel
    ALIAS morpheus::gfx::intel
    FOLDER "Libraries/Gfx/Intel"
)

target_include_directories(MorpheusGfxIntel
	PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxIntel
	PUBLIC
		morpheus::gfx::platform
	PRIVATE
		intel::GraphicsControlLibrary
)

add_subdirectory(morpheus/gfx/intel)