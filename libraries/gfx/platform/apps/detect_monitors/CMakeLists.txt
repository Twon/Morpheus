morpheus_add_executable(
    NAME detect_monitors
	ALIAS morpheus::detect_monitors
    FOLDER "Libraries/Gfx/Platform"
)
target_sources(detect_monitors
    PRIVATE
        main.cpp
)
target_link_libraries(detect_monitors
	PRIVATE
		MorpheusGfxPlatform
)
