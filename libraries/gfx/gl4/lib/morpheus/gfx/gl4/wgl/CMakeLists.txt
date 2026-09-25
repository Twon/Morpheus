target_sources(MorpheusGfxGL4
    PUBLIC
        FILE_SET HEADERS
        FILES
            adapter.hpp
            context.hpp
            render_window.hpp
            verify.hpp
            video_mode.hpp
    PRIVATE
        adapter.cpp
        context.cpp
        render_window.cpp
        video_mode.cpp
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
