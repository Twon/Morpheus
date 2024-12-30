FetchContent_Declare(
    intelGraphicsControlLibrary
    GIT_REPOSITORY https://github.com/intel/drivers.gpu.control-library.git
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(intelGraphicsControlLibrary)

morpheus_add_library(
    NAME GraphicsControlLibrary
    ALIAS intel::GraphicsControlLibrary
)

target_include_directories(GraphicsControlLibrary
    PUBLIC
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
        $<BUILD_INTERFACE:${intelgraphicscontrollibrary_SOURCE_DIR}/include/>
)

target_sources(GraphicsControlLibrary
    PUBLIC
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/igcl_api.h>
        $<BUILD_INTERFACE:${intelgraphicscontrollibrary_SOURCE_DIR}/include/igcl_api.h>
    PRIVATE
        ${intelgraphicscontrollibrary_SOURCE_DIR}/Source/cApiWrapper.cpp
)
