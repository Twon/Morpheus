target_sources(MorpheusRenderSystemGL4
    PUBLIC
        adapter.hpp
        context.hpp
        verify.hpp
        video_mode.hpp
        window.cpp
    PRIVATE
        adapter.cpp
        context.cpp
        video_mode.cpp
        window.cpp
)

target_compile_options(MorpheusRenderSystemGL4
    PRIVATE
        
)

target_sources(MorpheusRenderSystemGL4Tests
    PRIVATE
        adapter.tests.cpp
        video_mode.tests.cpp
)

target_link_libraries(MorpheusRenderSystemGL4Tests
    PRIVATE
        Boost::filesystem
)
#[[find_package(OpenCL REQUIRED)
target_link_libraries(MorpheusRenderSystemGL4Tests
    PRIVATE
        OpenCL::OpenCL
)#]]