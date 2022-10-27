target_sources(MorpheusCore
    PUBLIC
        format.hpp
        print.hpp
        ranges.hpp
        source_location.hpp
        version.hpp
)

find_package(fmt REQUIRED)
find_package(tl-expected REQUIRED)
find_package(range-v3 REQUIRED)

target_link_libraries(MorpheusCore
    PUBLIC
        fmt::fmt
        range-v3::range-v3
        tl::expected
)