morpheus_add_tests(
    NAME MorpheusAsanTests
    FOLDER "Libraries/Core"
)

find_package(ASan REQUIRED)
target_sources(MorpheusAsanTests
    PUBLIC
        asan.tests.cpp
)
