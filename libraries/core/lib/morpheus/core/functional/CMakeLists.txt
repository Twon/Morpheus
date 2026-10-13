add_subdirectory(concepts)

target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            curry.hpp
            function_ref.hpp
            overload.hpp
)

if (MORPHEUS_USE_MODULES)
    target_sources(MorpheusCore
        PUBLIC
            FILE_SET CXX_MODULES
            FILES functional.cppm
    )
endif()
