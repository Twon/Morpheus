target_sources(MorpheusGfxGL4
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

target_link_libraries(MorpheusGfxGL4
    PRIVATE
        Boost::filesystem
)
#[[find_package(OpenCL REQUIRED)
target_link_libraries(MorpheusRenderSystemGL4Tests
    PRIVATE
        OpenCL::OpenCL
)#]]
