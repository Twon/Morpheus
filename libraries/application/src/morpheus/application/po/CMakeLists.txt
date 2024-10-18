target_sources(MorpheusApplication
    PUBLIC
        FILE_SET HEADERS
        FILES
            config.hpp
            options.hpp
    PRIVATE
        config.cpp
)

target_link_libraries(MorpheusApplication
    PUBLIC
        Boost::program_options
)
