morpheus_add_library(
    NAME MorpheusCore
    ALIAS morpheus::core
    FOLDER "Libraries/Core"
)

target_include_directories(MorpheusCore
    PUBLIC
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(MorpheusCore
    PUBLIC
        morpheus::config
        Boost::headers
        Boost::log
        ctre::ctre
        magic_enum::magic_enum
)

add_subdirectory(morpheus/core)

target_compile_definitions(MorpheusCore
    PUBLIC
        $<$<PLATFORM_ID:Windows>:BOOST_USE_WINAPI_VERSION=BOOST_WINAPI_NTDDI_WIN10>
)

target_compile_options(MorpheusCore
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/wd4251> # class 'foo' needs to have dll-interface to be used by clients of class 'bar'
)
get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(MorpheusCore
    EXPORT_FILE_NAME export.hpp
)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/export.hpp ${CMAKE_CURRENT_BINARY_DIR}/morpheus/core/base/export.hpp COPYONLY)

install(TARGETS MorpheusCore
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/morpheus/core/base/export.hpp
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/morpheus/core/base/
)
