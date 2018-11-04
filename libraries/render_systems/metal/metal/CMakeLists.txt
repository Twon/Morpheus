if (APPLE)

	add_library(MorpheusRenderSystemMetal "")
	target_sources(MorpheusRenderSystemMetal
		PRIVATE
			"${CMAKE_CURRENT_LIST_DIR}/metal_render_system.hpp"
			"${CMAKE_CURRENT_LIST_DIR}/metal_render_system.mm"
	)

	target_compile_definitions(MorpheusRenderSystemMetal
		PUBLIC
			MORPHEUS_SHARED_BUILD=1
	)

	target_include_directories(MorpheusRenderSystemMetal
		PUBLIC
			"${CMAKE_CURRENT_LIST_DIR}/.."
	)

	target_link_libraries(MorpheusRenderSystemMetal
		PRIVATE
			MorpheusCore
	)

	set_target_properties(MorpheusRenderSystemMetal
		PROPERTIES
			 FOLDER "Libraries/RenderSystems"
	)

	set_target_properties(MorpheusRenderSystemMetal
		PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
			RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

	install (TARGETS MorpheusRenderSystemMetal
			 RUNTIME DESTINATION bin
			 ARCHIVE DESTINATION lib
			 LIBRARY DESTINATION lib
	)	
endif()
