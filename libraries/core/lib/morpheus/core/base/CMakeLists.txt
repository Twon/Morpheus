target_sources(MorpheusCore
    PUBLIC
        FILE_SET HEADERS
        FILES
            architecture.hpp
            cold.hpp
            compiler.hpp
            debugging.hpp
            exceptions.hpp
            platform.hpp
            prerequisites.hpp
            sanitizers.hpp
            scoped_action.hpp
    PRIVATE
        debugging.cpp
        exceptions.cpp
)

target_link_libraries(MorpheusCore
    PUBLIC
        libassert::assert
    PRIVATE
        Boost::unit_test_framework
)

# On windows copy libassert.dll to the same directory as the executable for your_target
if(WIN32)
    add_custom_target(MorpheusCoreDeployRuntime
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_RUNTIME_DLLS:MorpheusCore>
            $<TARGET_FILE_DIR:MorpheusCore>
        COMMAND_EXPAND_LISTS
        DEPENDS $<TARGET_RUNTIME_DLLS:MorpheusCore>
        VERBATIM
    )

    add_dependencies(MorpheusCore MorpheusCoreDeployLibAssert)
endif()
