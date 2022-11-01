target_sources(MorpheusCoreTests
    PUBLIC
        concept_checks.tests.cpp
        json_reader.tests.cpp
        json_writer.tests.cpp
        read_serialiser.tests.cpp
        write_serialiser.tests.cpp
)

add_subdirectory(adapters)