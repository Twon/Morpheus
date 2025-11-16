add_executable(RenderTriangle main.cpp)

find_package(ftxui)
target_link_libraries(RenderTriangle
    PRIVATE
        ftxui::ftxui
        morpheus::application
        morpheus::gfx::platform
        morpheus::gfx::gl4
        morpheus::vis
)

set_target_properties(RenderTriangle
    PROPERTIES
         FOLDER Examples/Gfx
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
