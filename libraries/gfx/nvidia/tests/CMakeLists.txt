morpheus_add_tests(
    NAME MorpheusGfxNVidiaTests
    FOLDER "Libraries/Gfx/NVidia"
)
target_sources(MorpheusGfxNVidiaTests
	PRIVATE
		driver.tests.cpp
)
target_link_libraries(MorpheusGfxNVidiaTests
	PRIVATE
		MorpheusGfxNVidia
)
