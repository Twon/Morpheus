add_executable(RenderTriangle main.cpp)

target_link_libraries(RenderTriangle
    PRIVATE
        morpheus::core
        morpheus::gfx::platform
)

set_target_properties(RenderTriangle
    PROPERTIES
         FOLDER Examples/Gfx
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)