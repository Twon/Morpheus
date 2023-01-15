morpheus_add_tests(
    NAME MorpheusGfxVulkanTests
    FOLDER "Libraries/Gfx/Vulkan"
)

target_sources(MorpheusGfxVulkanTests
    PRIVATE
        adapter.tests.cpp
        error_codes.tests.cpp
        #render_system.tests.cpp
        version.tests.cpp
        video_mode.tests.cpp
)

target_link_libraries(MorpheusGfxVulkanTests
    PRIVATE
        morpheus::gfx::vulkan
)

#set_tests_properties(MorpheusGfxVulkanTests PROPERTIES LABELS "GPU")
#catch_discover_tests(MorpheusGfxVulkanTests PROPERTIES LABELS "GPU")
