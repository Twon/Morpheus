morpheus_add_executable(NAME client)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(client PRIVATE client.cpp)
target_link_libraries(client PRIVATE morpheus::core)

morpheus_add_executable(NAME server)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(server PRIVATE server.cpp)
target_link_libraries(server PRIVATE morpheus::core)
