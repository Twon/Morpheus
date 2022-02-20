target_sources(MorpheusRenderSystemVulkan
    PRIVATE
		vulkan_instance.hpp
		vulkan_instance.cpp
)

target_sources(MorpheusRenderSystemVulkanTests
	PRIVATE
		vulkan_instance.tests.cpp
)
