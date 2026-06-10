target_sources(MorpheusCoreTests
    PRIVATE
        binary_reader.tests.cpp
        binary_roundtrip.tests.cpp
        binary_writer.tests.cpp
        concept_checks.tests.cpp
        exceptions.tests.cpp
        json_reader.tests.cpp
        json_roundtrip.tests.cpp
        json_writer.tests.cpp
        read_serialiser.tests.cpp
        write_serialiser.tests.cpp
)

add_subdirectory(adapters)
add_subdirectory(types)
