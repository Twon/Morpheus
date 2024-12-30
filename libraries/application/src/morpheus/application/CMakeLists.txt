target_sources(MorpheusApplication
    PUBLIC
        FILE_SET HEADERS
        FILES
            application.hpp
            try_catch.hpp
            version.hpp
    PRIVATE
        application.cpp
)

add_subdirectory(po)
