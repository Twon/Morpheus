morpheus_add_tests(
    NAME MorpheusCoreTests
    FOLDER "Libraries/Core"
)

target_sources(MorpheusCoreTests
    PRIVATE
        cpu.test.cpp
        generator.tests.cpp
)
 
#target_include_directories(MorpheusCoreTests
#    PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}/..
#
#)

target_link_libraries(MorpheusCoreTests
    PRIVATE
         morpheus::core
         morpheus::core::mocking
)

add_subdirectory(base)
add_subdirectory(conformance)
add_subdirectory(graph)
add_subdirectory(functional)
add_subdirectory(memory)
add_subdirectory(meta)
add_subdirectory(serialisation)