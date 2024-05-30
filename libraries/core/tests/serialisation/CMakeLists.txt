target_sources(MorpheusCoreTests
    PUBLIC
        binary_reader.tests.cpp
        binary_roundtrip.tests.cpp
        binary_writer.tests.cpp
        concept_checks.tests.cpp
        exceptions.tests.cpp
        json_reader.tests.cpp
        json_writer.tests.cpp
        yaml_reader.tests.cpp
        yaml_writer.tests.cpp
        read_serialiser.tests.cpp
        write_serialiser.tests.cpp
)

add_subdirectory(adapters)
