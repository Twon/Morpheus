find_package(Vulkan)

if (NOT ${Vulkan_FOUND})

    message("Vulkan not found on the system.  Unable to support Vulkan based render system.")

else()
    add_library(MorpheusRenderSystemVulkan "")
    add_executable(MorpheusRenderSystemVulkanTests "")

    add_subdirectory(adapters)

    target_sources(MorpheusRenderSystemVulkan
        PRIVATE
            vulkan_error_code.hpp
            vulkan_error_code.cpp
            vulkan_render_system.hpp
            vulkan_render_system.cpp
    )
    
    target_include_directories(MorpheusRenderSystemVulkan
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    #target_compile_definitions(MorpheusRenderSystemVulkan
    #    PUBLIC
    #        MORPHEUS_SHARED_BUILD=1
    #)

    target_link_libraries(MorpheusRenderSystemVulkan
        PRIVATE
            MorpheusCore
            Vulkan::Vulkan
    )
    
    get_target_property(SOURCES_FILES MorpheusRenderSystemVulkan SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

    target_sources(MorpheusRenderSystemVulkanTests
        PRIVATE
            vulkan_error_code.tests.cpp
            vulkan_render_system.tests.cpp
    )

    target_include_directories(MorpheusRenderSystemVulkanTests
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemVulkanTests
        PRIVATE
            MorpheusCore
            MorpheusRenderSystemVulkan
            Vulkan::Vulkan
            Catch2::Catch2
    )

    set_target_properties(MorpheusRenderSystemVulkan MorpheusRenderSystemVulkanTests
        PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS TRUE #$<OR:<$<BUILD_INTERFACE:TRUE>,$<INSTALL_INTERFACE:FALSE>>
            FOLDER "Libraries/RenderSystems/Vulkan"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    get_target_property(SOURCES_FILES_TEST MorpheusRenderSystemVulkanTests SOURCES)
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES_TEST})


	install (TARGETS MorpheusRenderSystemVulkan MorpheusRenderSystemVulkanTests
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )

    add_test(
        NAME MorpheusRenderSystemVulkanTests
        COMMAND MorpheusRenderSystemVulkanTests
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    catch_discover_tests(MorpheusRenderSystemVulkanTests)

endif()
