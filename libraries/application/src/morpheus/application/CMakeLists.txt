target_sources(
    MorpheusApplication
    PUBLIC application.hpp try_catch.hpp version.hpp
    PRIVATE application.cpp
)

add_subdirectory(po)
