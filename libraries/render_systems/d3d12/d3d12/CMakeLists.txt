if (WIN32)

    find_package(D3D12)

    if (NOT ${OD3D12_FOUND})

        message("D3D12 not found on the system.  Unable to support D3D12 based render system.")

    else()

        add_library(MorpheusRenderSystemD3D12 "")
        add_executable(MorpheusRenderSystemD3D12Test "")

        target_sources(MorpheusRenderSystemD3D12
            PUBLIC
                adapter.hpp
                render_system.hpp
                type_mapping.hpp
                verify.hpp
                video_mode.hpp
                video_mode_list.hpp
            PRIVATE
                adapter.cpp
                render_system.cpp
                type_mapping.cpp
                video_mode.cpp
                video_mode_list.cpp
        )

        #target_compile_definitions(MorpheusRenderSystemD3D12
        #    PUBLIC
        #        MORPHEUS_SHARED_BUILD=1
        #)

        target_include_directories(MorpheusRenderSystemD3D12
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        )

        target_include_directories(MorpheusRenderSystemD3D12Test
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
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
                Catch2::Catch2
        )

        set_target_properties(MorpheusRenderSystemD3D12 MorpheusRenderSystemD3D12Test
            PROPERTIES
                FOLDER "Libraries/RenderSystems/D3D12"
                ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

        target_sources(MorpheusRenderSystemD3D12Test
            PRIVATE
                adapter.tests.cpp
                video_mode_list.tests.cpp
        )

        install(TARGETS MorpheusRenderSystemD3D12
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

endif()
