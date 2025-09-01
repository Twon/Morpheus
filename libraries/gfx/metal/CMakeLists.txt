# Clang is expected for compiling for Objective-C++ (.mm) files when working with macOS system frameworks
if(${MORPHEUS_RENDER_SYSTEM_METAL})
    add_subdirectory(examples)
    add_subdirectory(lib)
    add_subdirectory(tests)
endif(${MORPHEUS_RENDER_SYSTEM_METAL})
