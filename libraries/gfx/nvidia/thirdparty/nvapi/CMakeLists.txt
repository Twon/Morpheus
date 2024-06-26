include(FetchContent)
FetchContent_Declare(
    nvapi
    URL https://download.nvidia.com/XFree86/nvapi-open-source-sdk/R550-OpenSource.tar
)
FetchContent_MakeAvailable(nvapi)

morpheus_add_library(
    NAME Nvapi
    ALIAS NVidia::Nvapi
)

target_include_directories(Nvapi
    PUBLIC
        ${nvapi_SOURCE_DIR}/R550-OpenSource
        $<BUILD_INTERFACE:${nvapi_SOURCE_DIR}/R550-OpenSource>
)

target_compile_options(Nvapi
    PRIVATE
         /wd4838
         /FIstddef.h
         /FI${nvapi_SOURCE_DIR}/R550-OpenSource/nvapi.h

)
target_sources(Nvapi
    PUBLIC
        ${nvapi_SOURCE_DIR}/R550-OpenSource/nvapi.h
        ${nvapi_SOURCE_DIR}/R550-OpenSource/nvapi_interface.h
        ${nvapi_SOURCE_DIR}/R550-OpenSource/NvApiDriverSettings.h
    PRIVATE
        ${nvapi_SOURCE_DIR}/R550-OpenSource/NvApiDriverSettings.c
)
set_source_files_properties(${nvapi_SOURCE_DIR}/R550-OpenSource/NvApiDriverSettings.c PROPERTIES LANGUAGE CXX)

set_target_properties(Nvapi
    PROPERTIES
        FOLDER "Thirdparty"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS Nvapi
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
