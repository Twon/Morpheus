morpheus_add_tests(
    NAME MorpheusApplicationTests
    FOLDER "Libraries/Application"
)

target_link_libraries(MorpheusApplicationTests
    PRIVATE
         MorpheusCore
         morpheus::application
)

add_subdirectory(po)
