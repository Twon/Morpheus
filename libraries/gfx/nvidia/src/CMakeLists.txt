morpheus_add_library(
    NAME MorpheusGfxNVidia 
    ALIAS morpheus::gfx::nvidia
    FOLDER "Libraries/Gfx/NVidia"
)

target_include_directories(MorpheusGfxNVidia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxNVidia
	PUBLIC
        morpheus::gfx::platform
		NVidia::NvapiHeaders
)

set_target_properties(MorpheusGfxNVidia
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/gfx/nvidia)