morpheus_add_tests(
    NAME MorpheusApplicationTests
    FOLDER "Libraries/Application"
)

target_sources(MorpheusApplicationTests
    PRIVATE
        application.tests.cpp
        version.tests.cpp
)

target_link_libraries(MorpheusApplicationTests
    PRIVATE
         MorpheusCore
         morpheus::application
)

add_subdirectory(po)
