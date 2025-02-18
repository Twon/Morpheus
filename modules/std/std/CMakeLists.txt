add_library(std)
target_sources(std
    PUBLIC
        FILE_SET CXX_MODULES TYPE CXX_MODULES
        FILES
            "std.ixx"
)

target_compile_features(std PUBLIC cxx_std_23)
