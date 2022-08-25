add_library(MorpheusCore "")
add_executable(MorpheusCoreTests "")

target_include_directories(MorpheusCore
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>
)

target_sources(MorpheusCore
    PUBLIC
        cpu.hpp
        game/game.hpp
        world/world_model.hpp
        visualisation/visualisation.hpp
    PRIVATE
        cpu.cpp
        game/game.cpp
        world/world_model.cpp
        visualisation/visualisation.cpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        cpu.test.cpp
)

add_subdirectory(base)
add_subdirectory(conformance)
add_subdirectory(concurrency)
add_subdirectory(gfx)
add_subdirectory(meta)
add_subdirectory(serialisation)





target_include_directories(MorpheusCoreTests
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
)

#target_compile_definitions(MorpheusCore
#    PUBLIC
#         MORPHEUS_SHARED_BUILD=1
#         MORPHEUS_DLL_EXPORTS=1
#)

target_compile_options(MorpheusCore
    PRIVATE
#        -enable-hosted-libstdcxx
	    $<$<CXX_COMPILER_ID:MSVC>:/wd4251> # class 'foo' needs to have dll-interface to be used by clients of class 'bar'
)

target_link_libraries(MorpheusCore
    PUBLIC
        Boost::headers
        fmt::fmt
        range-v3::range-v3
)

target_link_libraries(MorpheusCoreTests
    PRIVATE
         Catch2::Catch2
         MorpheusCore
)

set_target_properties(MorpheusCore MorpheusCoreTests
    PROPERTIES
        FOLDER "Libraries/Core"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

get_target_property(TEST_SOURCES_FILES MorpheusCoreTests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_SOURCES_FILES})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(MorpheusCore)

install(TARGETS MorpheusCore
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

# Hierarchically copy headers to the install dir
install (
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/../core
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/core
    FILES_MATCHING PATTERN
        "*.hpp"
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/morpheuscore_export.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/core
)

add_test(
    NAME MorpheusCoreTests
    COMMAND MorpheusCoreTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
catch_discover_tests(MorpheusCoreTests)
add_coverage(MorpheusCore)
add_coverage(MorpheusCoreTests)
