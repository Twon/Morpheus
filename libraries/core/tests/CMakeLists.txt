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
         MorpheusCore
)

get_target_property(TEST_SOURCES_FILES MorpheusCoreTests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_SOURCES_FILES})

add_subdirectory(base)
add_subdirectory(functional)
add_subdirectory(memory)
add_subdirectory(meta)
add_subdirectory(serialisation)