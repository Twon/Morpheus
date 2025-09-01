add_subdirectory(std)

target_sources(MorpheusApplication
    PUBLIC
        FILE_SET HEADERS
        FILES
            enums.hpp
            scannable.hpp
)
