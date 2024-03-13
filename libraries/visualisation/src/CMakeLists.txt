morpheus_add_library(
    NAME MorpheusVisualisation
    ALIAS morpheus::vis
    FOLDER "Libraries/Vis"
)

target_include_directories(MorpheusVisualisation
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusVisualisation
	PUBLIC
		morpheus::core
        morpheus::gfx::platform
)

set_target_properties(MorpheusVisualisation
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/vis)
