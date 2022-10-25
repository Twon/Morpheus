target_sources(MorpheusCore
    PUBLIC
        generator.hpp
)

#include(CheckStandardLibrary)
#CheckStandardLibrary(RETURN_VALUE isLibCxx)
#message(STATUS "This is an error: ${isLibCxx}")

#[[
target_compile_options(MorpheusCore
    PUBLIC
        $<$<AND:$<BOOL:${MORPHEUS_USE_LIBSTDCXX}>,$<CXX_COMPILER_ID:Clang>>:-stdlib=libstdc++>
        $<$<AND:$<NOT:${MORPHEUS_USE_LIBSTDCXX}>,$<CXX_COMPILER_ID:GCC>>:-nostdinc++ -lc++abi>
)
]]

target_sources(MorpheusCoreTests
    PUBLIC
        generator.tests.cpp
)