morpheus_add_testing_library(
	NAME MorpheusCoreTesting
	ALIAS morpheus::core::testing
	FOLDER "Libraries/Core"
)

target_include_directories(MorpheusCoreTesting
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MorpheusCoreTesting
    PUBLIC
        morpheus::core
        Boost::filesystem
)

set_target_properties(MorpheusCoreTesting
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus)
