target_sources(MorpheusCoreTesting
	PUBLIC
		assert.hpp
		gmock.hpp
	PRIVATE
		assert.cpp
		gmock.cpp
)

target_compile_definitions(MorpheusCoreTesting
	PUBLIC
	    GTEST_DONT_DEFINE_FAIL
	    GTEST_DONT_DEFINE_SUCCEED
)

add_subdirectory(std)