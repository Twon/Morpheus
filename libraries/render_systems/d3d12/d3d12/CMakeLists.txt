if (WIN32)

    find_package(D3D12)

    if (NOT ${OD3D12_FOUND})

        message("D3D12 not found on the system.  Unable to support D3D12 based render system.")

    else()

        add_library(MorpheusRenderSystemD3D12 "")
        add_executable(MorpheusRenderSystemD3D12Test "")

        add_subdirectory(adapters)

        target_sources(MorpheusRenderSystemD3D12
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/d3d12_render_system.hpp"
                "${CMAKE_CURRENT_LIST_DIR}/d3d12_render_system.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/d3d12_type_mapping.hpp"
                "${CMAKE_CURRENT_LIST_DIR}/d3d12_type_mapping.cpp"
        )

        #target_compile_definitions(MorpheusRenderSystemD3D12
        #    PUBLIC
        #        MORPHEUS_SHARED_BUILD=1
        #)

        target_include_directories(MorpheusRenderSystemD3D12
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
        )

        target_include_directories(MorpheusRenderSystemD3D12Test
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
        )

        target_link_libraries(MorpheusRenderSystemD3D12
			PUBLIC
                MorpheusCore
                D3D12::DXGI
                D3D12::D3D12
        )

        target_link_libraries(MorpheusRenderSystemD3D12Test
            PRIVATE
                MorpheusCore
                D3D12::DXGI
                D3D12::D3D12
				catch2::catch2
        )

        set_target_properties(MorpheusRenderSystemD3D12 MorpheusRenderSystemD3D12Test
            PROPERTIES
                 FOLDER "Libraries/RenderSystems/D3D12"
        )

        set_target_properties(MorpheusRenderSystemD3D12 MorpheusRenderSystemD3D12Test
            PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

		get_target_property(SOURCES_FILES MorpheusRenderSystemD3D12 SOURCES)
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

		get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemD3D12Test SOURCES)
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})

        target_sources(MorpheusRenderSystemD3D12Test
            PRIVATE
                ${SOURCES_FILES}
        )

        install (TARGETS MorpheusRenderSystemD3D12
                 RUNTIME DESTINATION bin
                 ARCHIVE DESTINATION lib
                 LIBRARY DESTINATION lib
        )
    endif()

endif()
