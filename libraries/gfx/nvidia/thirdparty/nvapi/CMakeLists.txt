include(FetchContent)
FetchContent_Declare(
    nvapi
    GIT_REPOSITORY https://github.com/NVIDIA/nvapi.git
	GIT_TAG main
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nvapi)

add_library(Nvapi STATIC)
add_library(NVidia::Nvapi ALIAS Nvapi)
target_include_directories(Nvapi
    PUBLIC
        $<BUILD_INTERFACE:${nvidiaAPI_SOURCE_DIR}>
)

target_sources(Nvapi
	PUBLIC
	    ${nvapi_SOURCE_DIR}/nvapi.h
		${nvapi_SOURCE_DIR}/nvapi_lite_common.h
		${nvapi_SOURCE_DIR}/nvapi_lite_d3dext.h
		${nvapi_SOURCE_DIR}/nvapi_lite_salend.h
		${nvapi_SOURCE_DIR}/nvapi_lite_salstart.h
		${nvapi_SOURCE_DIR}/nvapi_lite_sli.h
		${nvapi_SOURCE_DIR}/nvapi_lite_stereo.h
		${nvapi_SOURCE_DIR}/nvapi_lite_surround.h
		${nvapi_SOURCE_DIR}/NvApiDriverSettings.h
		${nvapi_SOURCE_DIR}/nvHLSLExtns.h
		${nvapi_SOURCE_DIR}/nvHLSLExtnsInternal.h
		${nvapi_SOURCE_DIR}/nvShaderExtnEnums.h
	PRIVATE
	    ${nvapi_SOURCE_DIR}/NvApiDriverSettings.c
)

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
