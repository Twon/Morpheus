
if (NOT APPLE)
    message(STATUS "Not an Apple system.  Unable to support Metal based render system.")
    return()
endif()

find_package(moltenvk REQUIRED)
if (NOT APPLE)
    message("Metal not found on the system.  Unable to support Metal based render system.")
    return()
endif()

list(APPEND LANGUAGES OBJCXX)

add_library(MorpheusRenderSystemMetal "")
target_sources(MorpheusRenderSystemMetal
    PUBLIC
        adapter.hpp
        adapter_list.hpp
        metal_render_system.hpp
        video_mode.hp
        video_mode_list.hpp
    PRIVATE
        adapter.cpp
        adapter_list.cpp
        metal_render_system.mm
        video_mode.cpp
        video_mode_list.cpp
)

target_compile_definitions(MorpheusRenderSystemMetal
    PUBLIC
        MORPHEUS_SHARED_BUILD=1
)

target_include_directories(MorpheusRenderSystemMetal
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(MorpheusRenderSystemMetal
    PRIVATE
        MorpheusCore
    PRIVATE
        moltenvk::moltenvk
)

add_executable(MorpheusRenderSystemMetalTests "")
target_sources(MorpheusRenderSystemMetalTests
    PRIVATE
        adapter_list.test.cpp
        video_mode_list.test.cpp
)

set_target_properties(MorpheusRenderSystemMetal
    PROPERTIES
        CMAKE_OBJCXX_STANDARD 20
        CMAKE_OBJCXX_STANDARD_REQUIRED ON
        CMAKE_OBJCXX_EXTENSIONS OFF
)

set_target_properties(MorpheusRenderSystemMetal
    PROPERTIES
        FOLDER Libraries/RenderSystems/Metal
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS MorpheusRenderSystemMetal
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_test(
    NAME MorpheusRenderSystemMetalTests
    COMMAND MorpheusRenderSystemMetalTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
catch_discover_tests(MorpheusRenderSystemMetalTests)
add_coverage(MorpheusRenderSystemMetal)

