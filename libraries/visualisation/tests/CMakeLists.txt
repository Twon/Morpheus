morpheus_add_tests(
    NAME MorpheusVisualisationTests
    FOLDER "Libraries/Vis"
)

target_sources(MorpheusVisualisationTests
    PRIVATE
        render_system_factory.tests.cpp
)

target_link_libraries(MorpheusVisualisationTests
    PRIVATE
        morpheus::vis
)
