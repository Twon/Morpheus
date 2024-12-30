add_subdirectory(std)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            enum.hpp
)
