FetchContent_Declare(
    NVApi
    GIT_REPOSITORY https://github.com/NVIDIA/nvapi.git
	GIT_TAG main
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(NVApi)




add_library(NvapiHeaders STATIC)
add_library(NVidia::NvapiHeaders ALIAS NvapiHeaders)
target_include_directories(NvapiHeaders
    PUBLIC
        $<BUILD_INTERFACE:${NVApi_SOURCE_DIR}>
)

target_sources(NvapiHeaders
	PUBLIC
	    ${NVApi_SOURCE_DIR}/nvapi.h
		${NVApi_SOURCE_DIR}/nvapi_lite_common.h
		${NVApi_SOURCE_DIR}/nvapi_lite_d3dext.h
		${NVApi_SOURCE_DIR}/nvapi_lite_salend.h
		${NVApi_SOURCE_DIR}/nvapi_lite_salstart.h
		${NVApi_SOURCE_DIR}/nvapi_lite_sli.h
		${NVApi_SOURCE_DIR}/nvapi_lite_stereo.h
		${NVApi_SOURCE_DIR}/nvapi_lite_surround.h
		${NVApi_SOURCE_DIR}/NvApiDriverSettings.h
		${NVApi_SOURCE_DIR}/nvHLSLExtns.h
		${NVApi_SOURCE_DIR}/nvHLSLExtnsInternal.h
		${NVApi_SOURCE_DIR}/nvShaderExtnEnums.h
	PRIVATE
	    ${NVApi_SOURCE_DIR}/NvApiDriverSettings.cpp
)

set_target_properties(NvapiHeaders
    PROPERTIES
        FOLDER "Thirdparty"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS NvapiHeaders
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
