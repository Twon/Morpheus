target_sources(
    MorpheusApplication
    PUBLIC config.hpp options.hpp
    PRIVATE config.cpp
)

target_link_libraries(MorpheusApplication PUBLIC Boost::program_options)
