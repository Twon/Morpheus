add_library(MorpheusGfxIntel "")
target_include_directories(MorpheusGfxIntel
	PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxIntel
	PUBLIC
		MorpheusCore
	PRIVATE
		intel::GraphicsControlLibrary
)


add_executable(MorpheusGfxIntelTests)
target_link_libraries(MorpheusGfxIntelTests
	PRIVATE
		MorpheusGfxIntel
		Catch2::Catch2
		intel::GraphicsControlLibrary
)

set_target_properties(MorpheusGfxIntel MorpheusGfxIntelTests
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        FOLDER "Libraries/RenderSystems/Intel"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS MorpheusGfxIntel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_subdirectory(morpheus/gfx/intel)