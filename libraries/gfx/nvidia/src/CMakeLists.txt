add_library(MorpheusGfxNVidia)
target_include_directories(MorpheusGfxNVidia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxNVidia
	PUBLIC
        MorpheusCore
		NVidia::NvapiHeaders
)

add_executable(MorpheusGfxNVidiaTests)
target_link_libraries(MorpheusGfxNVidiaTests
	PRIVATE
		MorpheusGfxNVidia
        Catch2::Catch2
)

set_target_properties(MorpheusGfxNVidia MorpheusGfxNVidiaTests
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        FOLDER "Libraries/RenderSystems/NVidia"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS MorpheusGfxNVidia
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_subdirectory(morpheus/gfx/nvidia)