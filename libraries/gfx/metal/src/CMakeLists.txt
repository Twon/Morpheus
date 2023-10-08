find_package(moltenvk REQUIRED)
if (NOT ${moltenvk_FOUND})
    message("Metal VK not found.  Unable to support Metal based render system.")
    return()
endif()

list(APPEND LANGUAGES OBJCXX)

morpheus_add_library(
    NAME MorpheusGfxMetal
    ALIAS morpheus::gfx::metal
    FOLDER "Libraries/Gfx/Metal"
)

target_include_directories(MorpheusGfxMetal
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(MorpheusGfxMetal
    PUBLIC
        morpheus::gfx::platform
)

add_subdirectory(morpheus/gfx/metal)
