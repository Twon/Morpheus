morpheus_add_library(
    NAME MorpheusVisualisation
    ALIAS morpheus::vis
    FOLDER "Libraries/Vis"
)

target_include_directories(MorpheusVisualisation
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusVisualisation
    PUBLIC
        morpheus::application
        morpheus::core
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_DIRECT_X12}>:morpheus::gfx::d3d12>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_METAL}>:morpheus::gfx::metal>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_OPENGL}>:morpheus::gfx::gl4>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_VULKAN}>:morpheus::gfx::vulkan>
        morpheus::gfx::platform
)

target_compile_definitions(MorpheusVisualisation
    PUBLIC
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_DIRECT_X12}>:MORPHEUS_RENDER_SYSTEM_DIRECT_X12=1>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_METAL}>:MORPHEUS_RENDER_SYSTEM_METAL=1>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_OPENGL}>:MORPHEUS_RENDER_SYSTEM_OPENGL=1>
        $<$<BOOL:${MORPHEUS_RENDER_SYSTEM_VULKAN}>:MORPHEUS_RENDER_SYSTEM_VULKAN=1>
)

set_target_properties(MorpheusVisualisation
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/vis)
