target_sources(MorpheusCore
    PUBLIC
        dispatch.hpp
        fundamentals.hpp
        json_reader.hpp
        json_writer.hpp
        read_serialiser.hpp
        serialise.hpp
        text_writer.hpp
        write_serialiser.hpp
    PRIVATE
        json_reader.cpp
        json_writer.cpp
)

target_sources(MorpheusCoreTests
    PUBLIC
        json_reader.tests.cpp
        json_writer.tests.cpp
        write_serialiser.tests.cpp
)

find_package(RapidJSON REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        RapidJSON::RapidJSON
)

add_subdirectory(adapters)
add_subdirectory(concepts)