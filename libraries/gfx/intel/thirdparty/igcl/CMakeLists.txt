FetchContent_Declare(
    intelGraphicsControlLibrary
    GIT_REPOSITORY https://github.com/intel/drivers.gpu.control-library.git
)
FetchContent_MakeAvailable(intelGraphicsControlLibrary)

morpheus_add_library(
    NAME GraphicsControlLibrary
    ALIAS intel::GraphicsControlLibrary
)

add_library(GraphicsControlLibrary)
add_library(intel::GraphicsControlLibrary ALIAS GraphicsControlLibrary)

target_include_directories(GraphicsControlLibrary
    PUBLIC
        ${intelgraphicscontrollibrary_SOURCE_DIR}/include/
)

target_sources(GraphicsControlLibrary
    PUBLIC
        ${intelgraphicscontrollibrary_SOURCE_DIR}/include/igcl_api.h
    PRIVATE
        ${intelgraphicscontrollibrary_SOURCE_DIR}/Source/cApiWrapper.cpp
)

set_target_properties(GraphicsControlLibrary
    PROPERTIES
        FOLDER "Thirdparty"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS GraphicsControlLibrary
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
