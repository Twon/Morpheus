add_library(NvapiHeaders STATIC)
add_library(NVidia::NvapiHeaders ALIAS NvapiHeaders)
target_include_directories(NvapiHeaders
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources(NvapiHeaders
	PUBLIC
		nvapi.h
		nvapi_lite_common.h
		nvapi_lite_d3dext.h
		nvapi_lite_salend.h
		nvapi_lite_salstart.h
		nvapi_lite_sli.h
		nvapi_lite_stereo.h
		nvapi_lite_surround.h
		NvApiDriverSettings.h
		nvHLSLExtns.h
		nvHLSLExtnsInternal.h
		nvShaderExtnEnums.h
	PRIVATE
		NvApiDriverSettings.cpp
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
