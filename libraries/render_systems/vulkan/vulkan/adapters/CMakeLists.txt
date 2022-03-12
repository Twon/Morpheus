target_sources(MorpheusRenderSystemVulkan
    PRIVATE
        vulkan_adapter.hpp
        vulkan_adapter.cpp
        vulkan_adapter_list.hpp
        vulkan_adapter_list.cpp
        vulkan_video_mode.hpp
        vulkan_video_mode.cpp
        vulkan_video_mode_list.hpp
        vulkan_video_mode_list.cpp
)

target_sources(MorpheusRenderSystemVulkanTests
	PRIVATE
		vulkan_adapter_list.tests.cpp
		vulkan_video_mode_list.tests.cpp
        CMakeLists.txt
)
