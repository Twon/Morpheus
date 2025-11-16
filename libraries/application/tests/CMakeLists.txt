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
        morpheus::application
)

add_subdirectory(po)

if(APPLE)
    set_tests_properties(MorpheusApplicationTests PROPERTIES ENVIRONMENT "TZDIR=/var/db/timezone/zoneinfo")
elseif(UNIX)
    set_tests_properties(MorpheusApplicationTests PROPERTIES ENVIRONMENT "TZDIR=/usr/share/zoneinfo")
endif()
