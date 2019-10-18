find_package(Vulkan)

if (NOT ${Vulkan_FOUND})

    message("Vulkan not found on the system.  Unable to support Vulkan based render system.")

else()
    add_library(MorpheusRenderSystemVulkan "")
    add_executable(MorpheusRenderSystemVulkanTest "")

    add_subdirectory(adapters)

    target_sources(MorpheusRenderSystemVulkan
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/vulkan_render_system.hpp"
            "${CMAKE_CURRENT_LIST_DIR}/vulkan_render_system.cpp"
    )

    #target_compile_definitions(MorpheusRenderSystemVulkan
    #    PUBLIC
    #        MORPHEUS_SHARED_BUILD=1
    #)

    target_include_directories(MorpheusRenderSystemVulkanTest
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_include_directories(MorpheusRenderSystemVulkan
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemVulkan
        PRIVATE
            MorpheusCore
			Vulkan::Vulkan
    )

    target_link_libraries(MorpheusRenderSystemVulkanTest
        PRIVATE
            MorpheusCore
			Vulkan::Vulkan
            catch2::catch2
    )

    set_target_properties(MorpheusRenderSystemVulkan MorpheusRenderSystemVulkanTest
        PROPERTIES
             FOLDER "Libraries/RenderSystems/Vulkan"
    )

    set_target_properties(MorpheusRenderSystemVulkan MorpheusRenderSystemVulkanTest
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    get_target_property(SOURCES_FILES MorpheusRenderSystemVulkan SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

    get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemVulkanTest SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})

    target_sources(MorpheusRenderSystemVulkanTest
        PRIVATE
            ${SOURCES_FILES}
    )

	install (TARGETS MorpheusRenderSystemVulkan
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )

endif()
