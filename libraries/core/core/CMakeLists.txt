add_library(MorpheusCore "")

target_sources(MorpheusCore
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/cpu.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/platform.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/game/game.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_system_factory.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_system.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_target.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_window.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/world/world_model.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/visualisation/visualisation.hpp"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/cpu.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/game/game.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_system_factory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_system.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_target.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/gfx/render_window.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/world/world_model.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/visualisation/visualisation.cpp"
)

if(WIN32)
    add_subdirectory(gfx/win32)
endif(WIN32)

add_subdirectory(gfx/textures)

get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

target_include_directories(MorpheusCore
    PUBLIC
        "$<INSTALL_INTERFACE:include/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>"
)

target_compile_definitions(MorpheusCore 
    PUBLIC 
         MORPHEUS_SHARED_BUILD=1
         MORPHEUS_DLL_EXPORTS=1
)

set_target_properties(MorpheusCore
    PROPERTIES
        FOLDER "Libraries"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

include(GenerateExportHeader)
generate_export_header(MorpheusCore)

install (TARGETS MorpheusCore
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         PUBLIC_HEADER DESTINATION include/core
)

# Hierarchically copy headers to the install dir
install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../core" DESTINATION include FILES_MATCHING PATTERN "*.hpp" )
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/morpheuscore_export.h" DESTINATION include/core )

add_executable(TestMorpheusCore "")

target_include_directories(TestMorpheusCore
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/.."
)

target_sources(TestMorpheusCore
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/cpu.test.cpp"
)

target_link_libraries(TestMorpheusCore
    PRIVATE
         catch2::catch2
         MorpheusCore
)

set_target_properties(TestMorpheusCore PROPERTIES FOLDER "Tests")
set_target_properties(TestMorpheusCore
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
