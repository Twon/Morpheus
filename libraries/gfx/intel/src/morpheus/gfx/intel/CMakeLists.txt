target_sources(MorpheusGfxIntel
    PUBLIC
        adapter.hpp
    PRIVATE
        adapter.cpp
)

target_sources(MorpheusGfxIntelTests
    PRIVATE
        adapter.tests.cpp
)