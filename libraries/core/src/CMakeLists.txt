morpheus_add_library(
    NAME MorpheusCore
    ALIAS morpheus::core
    FOLDER "Libraries/Core"
)

target_include_directories(MorpheusCore
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
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
#         MORPHEUS_SHARED_BUILD=1
#         MORPHEUS_DLL_EXPORTS=1
        BOOST_USE_WINAPI_VERSION=0x600
)

target_compile_options(MorpheusCore
    PRIVATE
#        -enable-hosted-libstdcxx
	    $<$<CXX_COMPILER_ID:MSVC>:/wd4251> # class 'foo' needs to have dll-interface to be used by clients of class 'bar'
)
get_target_property(SOURCES_FILES MorpheusCore SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(MorpheusCore)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/morpheuscore_export.h ${CMAKE_CURRENT_BINARY_DIR}/morpheus/core/morpheuscore_export.h COPYONLY)

install(TARGETS MorpheusCore
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

# Hierarchically copy headers to the install dir
install (
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/morpheus/core
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/morpheus/core
    FILES_MATCHING PATTERN
        "*.hpp"
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/morpheus/core/morpheuscore_export.h
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/morpheus/core/
)
