morpheus_add_executable(NAME EchoServer)
target_sources(EchoServer
    PRIVATE
         main.cpp
)

target_link_libraries(EchoServer
    PRIVATE
        morpheus::application
        morpheus::core
)

set_target_properties(EchoServer
    PROPERTIES
         FOLDER Examples/Network
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
