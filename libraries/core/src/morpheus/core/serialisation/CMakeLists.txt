target_sources(MorpheusCore
    PUBLIC
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
        write_serialiser.hpp
        write_serialiser_decl.hpp
        yaml_reader.hpp
        yaml_writer.hpp
     PRIVATE
        exceptions.cpp
        json_reader.cpp
        json_writer.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        rapidjson
        ryml::ryml  # https://conan.io/center/recipes/rapidyaml?version=0.5.0
)

add_subdirectory(adapters)
add_subdirectory(concepts)
