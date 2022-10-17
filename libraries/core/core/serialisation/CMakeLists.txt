target_sources(MorpheusCore
    PUBLIC
        fundamentals.hpp
        json_reader.hpp
        json_writer.hpp
        read_serialiser.hpp
        read_serialiser_decl.hpp
        serialise.hpp
        serialisers.hpp
        text_writer.hpp
        write_serialiser.hpp
        write_serialiser_decl.hpp
     PRIVATE
        json_reader.cpp
        json_writer.cpp
)

target_sources(MorpheusCoreTests
    PRIVATE
        concept_checks.tests.cpp
        json_reader.tests.cpp
        json_writer.tests.cpp
        read_serialiser.tests.cpp
        write_serialiser.tests.cpp
)

find_package(RapidJSON REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        RapidJSON::RapidJSON
)

add_subdirectory(adapters)
add_subdirectory(concepts)