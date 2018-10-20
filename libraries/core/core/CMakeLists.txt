add_library(MorpheusCore "")

if (WIN32)
#    set(GFX_WIN32_SOURCE_FILES ${GFX_WIN32_SOURCE_FILES} include/gfx/win32/win32_render_window.h)
#    set(GFX_WIN32_SOURCE_FILES ${GFX_WIN32_SOURCE_FILES} source/gfx/win32/win32_render_window.cpp)
#    source_group("gfx\\win32" FILES ${GFX_WIN32_SOURCE_FILES})
#    set(ALL_SOURCE_FILES ${ALL_SOURCE_FILES} ${GFX_WIN32_SOURCE_FILES} )
endif(WIN32)

target_sources(MorpheusCore
    PUBLIC
	    cpu.hpp
		platform.hpp
		game/game.hpp
		gfx/render_system.hpp
        gfx/render_target.hpp
        gfx/render_window.hpp
		world/world_model.hpp
		visualisation/visualisation.hpp
    PRIVATE
	    cpu.cpp
		game/game.cpp
		gfx/render_system.cpp
        gfx/render_target.cpp
        gfx/render_window.cpp
		world/world_model.cpp
		visualisation/visualisation.cpp
)

if(WIN32)
add_subdirectory(gfx/win32)
endif(WIN32)

get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

target_include_directories(MorpheusCore
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/.."
)

target_compile_definitions(MorpheusCore 
    PUBLIC 
	     MORPHEUS_SHARED_BUILD=1
		 MORPHEUS_DLL_EXPORTS=1
)

set_target_properties(MorpheusCore PROPERTIES FOLDER "Libraries")