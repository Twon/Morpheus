add_library(MorpheusCore "")
add_executable(MorpheusCoreTests "")

target_sources(MorpheusCore
    PRIVATE
        cpu.hpp
        platform.hpp
        game/game.hpp
        gfx/pixel.hpp
        gfx/render_system_factory.hpp
        gfx/render_system.hpp
        gfx/render_target.hpp
        gfx/render_window.hpp
        world/world_model.hpp
        visualisation/visualisation.hpp
    PRIVATE
        cpu.cpp
        game/game.cpp
        gfx/render_system_factory.cpp
        gfx/render_system.cpp
        gfx/render_target.cpp
        gfx/render_window.cpp
        world/world_model.cpp
        visualisation/visualisation.cpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        cpu.test.cpp
)

if(WIN32)
    add_subdirectory(gfx/win32)
endif(WIN32)

add_subdirectory(gfx/adapters)
add_subdirectory(gfx/textures)

target_sources(MorpheusCoreTests
    PRIVATE
        cpu.test.cpp
)

target_include_directories(MorpheusCore
    PUBLIC
        "$<INSTALL_INTERFACE:include/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..>"
)

target_include_directories(MorpheusCoreTests
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/.."
)

#target_compile_definitions(MorpheusCore
#    PUBLIC
#         MORPHEUS_SHARED_BUILD=1
#         MORPHEUS_DLL_EXPORTS=1
#)

target_compile_options(MorpheusCore
    PRIVATE
	    $<$<CXX_COMPILER_ID:MSVC>:/wd4251> # class 'foo' needs to have dll-interface to be used by clients of class 'bar'
)

target_link_libraries(MorpheusCore
    PUBLIC
        fmt::fmt
)

target_link_libraries(MorpheusCoreTests
    PRIVATE
         Catch2::Catch2
         MorpheusCore
)

set_target_properties(MorpheusCore MorpheusCoreTests
    PROPERTIES
        FOLDER "Libraries/Core"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

get_target_property(TEST_SOURCES_FILES MorpheusCoreTests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_SOURCES_FILES})

include(WriteCompilerDetectionHeader)
write_compiler_detection_header(
    FILE morpheuscore_compiler_detection.h
    PREFIX MORPHEUSCORE
    COMPILERS GNU Clang MSVC Intel AppleClang
    FEATURES cxx_constexpr
#    PROLOG "/// \\def"
#    EPILOG "///"
)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(MorpheusCore)

install (TARGETS MorpheusCore
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         PUBLIC_HEADER DESTINATION include/core
)

# Hierarchically copy headers to the install dir
install (
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/../core"
    DESTINATION
        include
    FILES_MATCHING PATTERN
        "*.hpp"
)

install(
    FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/morpheuscore_export.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/morpheuscore_compiler_detection.h"
    DESTINATION
        include/core
)

add_test(
    NAME MorpheusCoreTests
    COMMAND MorpheusCoreTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
catch_discover_tests(MorpheusCoreTests)
add_coverage(MorpheusCore)
add_coverage(MorpheusCoreTests)
