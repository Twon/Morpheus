find_package(Vulkan)

if (NOT ${Vulkan_FOUND})

    message("Vulkan not found on the system.  Unable to support Vulkan based render system.")

else()
    add_library(MorpheusRenderSystemVulkan "")
    target_sources(MorpheusRenderSystemVulkan
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/vulkan_render_system.hpp"
            "${CMAKE_CURRENT_LIST_DIR}/vulkan_render_system.cpp"
    )

    target_compile_definitions(MorpheusRenderSystemVulkan
        PUBLIC
            MORPHEUS_SHARED_BUILD=1
    )

    target_include_directories(MorpheusRenderSystemVulkan
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/.."
    )

    target_link_libraries(MorpheusRenderSystemVulkan
        PRIVATE
            MorpheusCore
    )

    set_target_properties(MorpheusRenderSystemVulkan
        PROPERTIES
             FOLDER "Libraries/RenderSystems"
    )

    set_target_properties(MorpheusRenderSystemVulkan
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    install (TARGETS MorpheusRenderSystemVulkan
             RUNTIME DESTINATION bin
             ARCHIVE DESTINATION lib
             LIBRARY DESTINATION lib
    )

endif()
