target_sources(MorpheusVisualisation
    PUBLIC
        FILE_SET HEADERS
        FILES
            render_system_factory.hpp
            tui.hpp
            visualisation.hpp
    PRIVATE
        render_system_factory.cpp
        tui.cpp
        visualisation.cpp
)
