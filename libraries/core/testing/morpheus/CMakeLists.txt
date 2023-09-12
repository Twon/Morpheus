target_sources(MorpheusCoreTesting
    PUBLIC
        logging.hpp
        redirect_stream.hpp
        temp_file.hpp
)

add_subdirectory(catch2)
add_subdirectory(serialisation)
