morpheus_add_library(
    NAME MorpheusApplication
    ALIAS morpheus::application
    FOLDER "Libraries/Application"
)

target_include_directories(
    MorpheusApplication PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# target_include_directories(MorpheusApplication PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> )

target_link_libraries(MorpheusApplication PUBLIC morpheus::core)

set_target_properties(MorpheusApplication PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_subdirectory(morpheus/application)
