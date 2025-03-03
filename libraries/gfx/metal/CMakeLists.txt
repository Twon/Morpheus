# Clang is expected for compiling for Objective-C++ (.mm) files when working with macOS system frameworks
if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" AND ${MORPHEUS_RENDER_SYSTEM_METAL})
    add_subdirectory(src)
    add_subdirectory(tests)
endif(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" AND ${MORPHEUS_RENDER_SYSTEM_METAL})