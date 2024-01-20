add_subdirectory(boost)
add_subdirectory(std)

target_sources(MorpheusApplicationTests
    PRIVATE
        enum.tests.cpp
)
