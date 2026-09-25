target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            aggregate.hpp
            hex.hpp
)

add_subdirectory(ankerl)
add_subdirectory(boost)
add_subdirectory(std)
