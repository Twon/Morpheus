add_executable(RenderTriangle main.cpp)

target_link_libraries(RenderTriangle
    PRIVATE
        MorpheusCore
)

set_target_properties(RenderTriangle
    PROPERTIES
         FOLDER "Examples/Gfx"
)

set_target_properties(RenderTriangle
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)