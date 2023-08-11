morpheus_add_tests(
    NAME MorpheusGfxNVidiaTests
    FOLDER "Libraries/Gfx/NVidia"
    LABELS GPU
)
target_sources(MorpheusGfxNVidiaTests
	PRIVATE
		driver.tests.cpp
)
target_link_libraries(MorpheusGfxNVidiaTests
	PRIVATE
		MorpheusGfxNVidia
)
