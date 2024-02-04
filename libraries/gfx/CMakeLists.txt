if(APPLE)
	add_subdirectory(metal)
endif(APPLE)

if(WIN32)
#	add_subdirectory(d3d12)
#	add_subdirectory(intel)
#	add_subdirectory(nvidia)
endif(WIN32)

#add_subdirectory(gl4)
add_subdirectory(platform)
#add_subdirectory(vulkan)
