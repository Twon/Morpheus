morpheus_add_executable(NAME client)
target_sources(client PRIVATE client.cpp)
target_link_libraries(client PRIVATE morpheus::core)

morpheus_add_executable(NAME server)
target_sources(server PRIVATE server.cpp)