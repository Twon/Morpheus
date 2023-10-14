morpheus_add_testing_library(
    INFERFACE
	NAME MorpheusCoreMocking
	ALIAS morpheus::core::mocking
	FOLDER "Libraries/Core"
)

target_include_directories(MorpheusCoreMocking
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MorpheusCoreMocking
    INTERFACE
        morpheus::core
)

set_target_properties(MorpheusCoreMocking
    PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

add_subdirectory(morpheus/core)
