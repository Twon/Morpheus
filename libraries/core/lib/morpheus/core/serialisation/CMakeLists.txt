find_package(RapidJSON REQUIRED)
find_package(tomlplusplus REQUIRED)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            binary_reader.hpp
            binary_writer.hpp
            exceptions.hpp
            fundamentals.hpp
            json_reader.hpp
            json_writer.hpp
            read_serialiser.hpp
            read_serialiser_decl.hpp
            serialise.hpp
            serialisers.hpp
            text_writer.hpp
            toml_reader.hpp
            toml_writer.hpp
            write_serialiser.hpp
            write_serialiser_decl.hpp
     PRIVATE
        exceptions.cpp
        json_reader.cpp
        json_writer.cpp
        toml_reader.cpp
        toml_writer.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        rapidjson
        tomlplusplus::tomlplusplus
)

add_subdirectory(adapters)
add_subdirectory(concepts)
