add_executable(MorpheusCoreTests)
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
         Catch2::Catch2
         MorpheusCore
)

set_target_properties(MorpheusCoreTests
    PROPERTIES
        FOLDER "Libraries/Core"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

get_target_property(TEST_SOURCES_FILES MorpheusCoreTests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_SOURCES_FILES})

add_test(
    NAME MorpheusCoreTests
    COMMAND MorpheusCoreTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
catch_discover_tests(MorpheusCoreTests)
#add_coverage(MorpheusCoreTests)

add_subdirectory(base)
add_subdirectory(functional)
add_subdirectory(memory)
add_subdirectory(meta)
add_subdirectory(serialisation)