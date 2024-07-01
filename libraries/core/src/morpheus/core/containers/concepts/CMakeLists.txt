add_subdirectory(detail)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            allocator_aware.hpp
            associative.hpp
            container.hpp
            contiguous.hpp
            reversible.hpp
            sequence.hpp
            unordered.hpp
)
