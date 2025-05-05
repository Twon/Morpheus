target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            cpu.hpp
    PRIVATE
        cpu.cpp
)

add_subdirectory(base)
add_subdirectory(concurrency)
add_subdirectory(conformance)
add_subdirectory(containers)
add_subdirectory(functional)
add_subdirectory(memory)
add_subdirectory(meta)
add_subdirectory(network)
add_subdirectory(serialisation)
