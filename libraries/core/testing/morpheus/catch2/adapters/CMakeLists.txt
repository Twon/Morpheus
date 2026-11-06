target_sources(MorpheusCoreTesting
    PUBLIC
        gmock.hpp
    PRIVATE
        gmock.cpp
)

target_compile_definitions(MorpheusCoreTesting
    PUBLIC
        GTEST_DONT_DEFINE_FAIL
        GTEST_DONT_DEFINE_SUCCEED
)
