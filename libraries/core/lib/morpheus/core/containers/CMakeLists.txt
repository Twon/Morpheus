add_subdirectory(concepts)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            unordered_dense.hpp
)

if (MORPHEUS_USE_MODULES)
    target_sources(MorpheusCore
        PUBLIC
            FILE_SET CXX_MODULES
            FILES containers.cppm
    )
endif()
