morpheus_add_tests(
    NAME MorpheusGfxIntelTests
    FOLDER "Libraries/Gfx/Intel"
)
target_sources(MorpheusGfxIntelTests
    PRIVATE
        adapter.tests.cpp
)
target_link_libraries(MorpheusGfxIntelTests
	PRIVATE
		MorpheusGfxIntel
)