morpheus_add_library(
    NAME MorpheusApplication
    ALIAS morpheus::application
    FOLDER "Libraries/Application"
)

target_include_directories(MorpheusApplication
    PUBLIC
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusApplication
    PUBLIC
        morpheus::core
)

set_target_properties(MorpheusApplication
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/application)
