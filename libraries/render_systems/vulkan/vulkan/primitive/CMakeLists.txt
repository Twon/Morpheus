target_sources(MorpheusRenderSystemVulkan
    PRIVATE
		vulkan_instance.hpp
		vulkan_instance.cpp
        "CMakeLists.txt"
)

set_source_files_properties(
    "${CMAKE_CURRENT_LIST_DIR}/CMakeList.txt"
    PROPERTIES
        HEADER_FILE_ONLY TRUE # Since it's just a text file, it doesn't need compiled
)

target_sources(MorpheusRenderSystemVulkanTests
	PRIVATE
		vulkan_instance.tests.cpp
        "CMakeLists.txt"
)
