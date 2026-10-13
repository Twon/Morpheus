target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
)

add_subdirectory(concepts)

if (MORPHEUS_USE_MODULES)
    target_sources(MorpheusCore
        PUBLIC
            FILE_SET CXX_MODULES
            FILES memory.cppm
    )
endif()