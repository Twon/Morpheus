set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(MorpheusConfig INTERFACE)
add_library(morpheus::config ALIAS MorpheusConfig)
target_link_libraries(MorpheusConfig
    INTERFACE
        $<$<PLATFORM_ID:Linux>:dl>
)
