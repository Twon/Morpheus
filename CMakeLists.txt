cmake_minimum_required(VERSION 3.12)

project(morpheus)

# Include necessary submodules
set(CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake"
)

include(Compiler)

enable_testing()

add_subdirectory(libraries)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Targets")