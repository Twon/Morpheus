add_subdirectory(adapters)
add_subdirectory(concepts)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            string.hpp
)

if (MORPHEUS_USE_MODULES)
    target_sources(MorpheusCore
        PUBLIC
            FILE_SET CXX_MODULES
            FILES conversion.cppm
    )
endif()
