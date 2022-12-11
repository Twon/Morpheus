include_guard(GLOBAL)

include(python)

option(ENABLE_CODE_COVERAGE "Enable code coverage" OFF)


#[=======================================================================[.rst:
get_all_targets
------------------

Overview
^^^^^^^^

#]=======================================================================]
function(get_all_targets)
    set(options)
    set(oneValueArgs RESULT DIRECTORY)
    set(multiValueArgs)
    cmake_parse_arguments(ALL_TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT ALL_TARGET_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()
    if (NOT ALL_TARGET_DIRECTORY)
        message(FATAL_ERROR "DIRECTORY parameter must be supplied")
    endif()

    get_property(subdirs DIRECTORY ${ALL_TARGET_DIRECTORY} PROPERTY SUBDIRECTORIES)
    foreach(subdir IN LISTS subdirs)
        get_all_targets(RESULT subTargets DIRECTORY ${subdir})
    endforeach()

    get_directory_property(allTargets DIRECTORY ${ALL_TARGET_DIRECTORY} BUILDSYSTEM_TARGETS)
    set(${ALL_TARGET_RESULT} ${subTargets} ${allTargets} PARENT_SCOPE)
endfunction()


#[=======================================================================[.rst:
coverage_target_filter_for_sources
------------------

Overview
^^^^^^^^

#]=======================================================================]
function(coverage_target_filter_for_sources)
    set(options)
    set(oneValueArgs RESULT)
    set(multiValueArgs TARGETS)
    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT COVERAGE_TARGETS)
        message(FATAL_ERROR "TARGETS parameter must be supplied")
    endif()
    if (NOT COVERAGE_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    foreach(target IN LISTS COVERAGE_TARGETS)
        get_target_property(TARGET_SOURCES ${target} SOURCES)
        if (NOT TARGET_SOURCES)
            continue()
        endif()

        list(APPEND targets ${target})
    endforeach()
    set(${COVERAGE_RESULT} ${${COVERAGE_RESULT}} ${targets} PARENT_SCOPE)

endfunction()


#[=======================================================================[.rst:
coverage_source_relative_path
------------------

Overview
^^^^^^^^

#]=======================================================================]
function (coverage_source_relative_path)
    set(options)
    set(oneValueArgs TARGET_NAME RESULT SOURCE_FILE)
    set(multiValueArgs)
    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT COVERAGE_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME parameter must be supplied")
    endif()
    if (NOT COVERAGE_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    get_target_property(TARGET_SOURCE_DIR ${COVERAGE_TARGET_NAME} SOURCE_DIR)
    get_target_property(TARGET_BINARY_DIR ${COVERAGE_TARGET_NAME} BINARY_DIR)

    # Generated files should be in the subdirectories of the targets binary directory
    string(REPLACE "${TARGET_BINARY_DIR}/" "" file "${COVERAGE_SOURCE_FILE}")

	if(IS_ABSOLUTE ${file})
		file(RELATIVE_PATH FILE ${TARGET_SOURCE_DIR} ${file})
 	endif()

	# get the right path for file
	string(REPLACE ".." "__" PATH "${file}")
    if (NOT PATH STREQUAL ${file})
        message(SEND_ERROR "TARGET_BINARY_DIR is ${TARGET_BINARY_DIR}")
        message(SEND_ERROR "PATH is ${PATH}")
        message(SEND_ERROR "file is ${file}")
    endif()

	set(${COVERAGE_RESULT} "${PATH}" PARENT_SCOPE)
endfunction()


#[=======================================================================[.rst:
coverage_target_clean_intermediate_file
------------------

Overview
^^^^^^^^

#]=======================================================================]
function(coverage_target_clean_intermediate_file)
    set(options QUIET)
    set(oneValueArgs TARGET_NAME)
    set(multiValueArgs)
    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT COVERAGE_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME parameter must be supplied")
    endif()

    get_target_property(TARGET_SOURCES ${COVERAGE_TARGET_NAME} SOURCES)
    get_target_property(TARGET_BINARY_DIR ${COVERAGE_TARGET_NAME} BINARY_DIR)

    foreach (file ${TARGET_SOURCES})
        list(APPEND GCOV_NOTE_FILES "${file}.gcno")
        list(APPEND GCOV_DATA_FILES "${file}.gcda")
    endforeach()

    set(EXPECTED_FILES ${GCOV_NOTE_FILES} ${GCOV_DATA_FILES})
    foreach (file ${EXPECTED_FILES})
        #message(STATUS "Original path ${file}")
        coverage_source_relative_path(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT file SOURCE_FILE ${file})
        set(INTERMEDIATE_FILE "CMakeFiles/${COVERAGE_TARGET_NAME}.dir/${file}")
#        if (NOT EXISTS ${TARGET_BINARY_DIR}/${INTERMEDIATE_FILE})
#            message(SEND_ERROR "Unable to locate ${TARGET_BINARY_DIR} / ${INTERMEDIATE_FILE} from ${CMAKE_CURRENT_BINARY_DIR} with original path ${FILE}")
#        endif()
		list(APPEND CLEAN_FILES INTERMEDIATE_FILE)
    endforeach()

    set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${INTERMEDIATE_FILE}")

endfunction()



function(code_coverage)
    set(options QUIET VERBOSE)
    set(oneValueArgs)
    set(multiValueArgs)

    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    get_filename_component(COMPILER_PATH "${CMAKE_CXX_COMPILER}" PATH)
    find_program(GCOV_BIN gcov HINTS ${COMPILER_PATH})
    if(NOT GCOV_BIN)
        message(SEND_ERROR "Unable to find gcov, disable code coverage to continue")
    endif()

    find_program(LCOV_BIN lcov)
    if(NOT LCOV_BIN)
        message(SEND_ERROR "Unable to find lcov, disable code coverage to continue")
    endif()

    find_program(GENHTML_BIN genhtml)
    if(NOT GENHTML_BIN)
        message(SEND_ERROR "Unable to find genhtml, disable code coverage to continue")
    endif()

    find_program(CPPFILT_BIN c++filt)
    if(NOT CPPFILT_BIN)
        message(SEND_ERROR "Unable to find c++filt, disable code coverage to continue")
    endif()

    if (NOT COVERAGE_QUIET)
        message(STATUS "Found gcov: ${GCOV_BIN}")
        message(STATUS "Found lcov: ${LCOV_BIN}")
        message(STATUS "Found genhtml: ${GENHTML_BIN}")
    endif()

    set(COVERAGE_VENV ${CMAKE_BINARY_DIR}/.venv/coverage)
    set(COVERAGE_FASTCOV_BIN ${COVERAGE_VENV}/bin/fastcov)
    set(COVERAGE_FASTCOV_TO_SONARQUBE_BIN ${COVERAGE_VENV}/bin/fastcov_to_sonarqube)
    create_python_virtualenv(
        DESTINATION ${COVERAGE_VENV}
        REQUIREMENTS ${PROJECT_SOURCE_DIR}/cmake/requirements/coverage_requirements.txt
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        OUTPUT
            ${COVERAGE_FASTCOV_BIN}
            ${COVERAGE_FASTCOV_TO_SONARQUBE_BIN}
    )

    set(COVERAGE_REPORT_DIR "${CMAKE_BINARY_DIR}/coverage")
    set(COVERAGE_REPORT_PATH "${COVERAGE_REPORT_DIR}/fastcov_report.json")
    set(SONARQUBE_REPORT_PATH "${COVERAGE_REPORT_DIR}/sonarcube_coverage.xml")
    set(LCOV_REPORT_PATH "${COVERAGE_REPORT_DIR}/lcov.info")
    set(LCOV_HTML_PATH "${COVERAGE_REPORT_DIR}/html")

#    string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" ROOT_SEARCH_DIR "${CMAKE_BINARY_DIR}")
#    message(STATUS "ROOT_SEARCH_DIR: ${ROOT_SEARCH_DIR}")

    get_all_targets(RESULT allTargets DIRECTORY ${PROJECT_SOURCE_DIR})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: All project targets: ${allTargets}")
    endif()
    
    coverage_target_filter_for_sources(RESULT targetsWithSource TARGETS ${allTargets})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: Targets with sources: ${targetsWithSource}}")
    endif()
    
    foreach(target IN LISTS targetsWithSource)
        get_target_property(TARGET_TYPE ${target} TYPE)
        message("Registering properties for target: ${target}:${TARGET_TYPE}")
#[[        target_compile_options(${target}
            PRIVATE
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-O0;-g;-fprofile-arcs;-ftest-coverage>
        )

        target_link_options(${target}
            PRIVATE
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-lgcov -coverage>
        )]]

        set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage")
        set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS "-lgcov -coverage")

        coverage_target_clean_intermediate_file(TARGET_NAME ${target})
    endforeach()

    file(MAKE_DIRECTORY ${COVERAGE_REPORT_DIR})

    add_custom_target(coverage-clean
        COMMAND
            ${COVERAGE_FASTCOV_BIN}
                --gcov ${GCOV_BIN}
                #--exclude ${CMAKE_CURRENT_BINARY_DIR}
                --include ${PROJECT_SOURCE_DIR}
                --zerocounters
        DEPENDS
            ${COVERAGE_FASTCOV_BIN}
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        COMMENT
            "Recursively delete all gcda files"
    )

    add_custom_target(coverage-fastcov
        COMMAND
            ${COVERAGE_FASTCOV_BIN}
                --gcov ${GCOV_BIN}
                #--exclude ${CMAKE_CURRENT_BINARY_DIR}
                --include ${PROJECT_SOURCE_DIR}
                -o ${COVERAGE_REPORT_PATH}
        DEPENDS
            ${COVERAGE_FASTCOV_BIN}
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        COMMENT
            "Distributed proccessing of coverage data collection and report generation"
    )

    add_custom_target(coverage)
    add_dependencies(coverage coverage-fastcov)

    add_custom_command(
        OUTPUT ${LCOV_REPORT_PATH}
        COMMAND
            ${COVERAGE_FASTCOV_BIN}
                --gcov ${GCOV_BIN}
                #--exclude ${CMAKE_CURRENT_BINARY_DIR}
                --include ${PROJECT_SOURCE_DIR}
                --lcov
                -o ${LCOV_REPORT_PATH}
        DEPENDS
            ${COVERAGE_FASTCOV_BIN}
            ${LCOV_BIN}
            # Missing source file (*.cpp and *.gcda) dependencies.
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        COMMENT
            "Distributed proccessing of coverage data collection and lcov report generation"
    )

    add_custom_target(coverage-lcov-info
        DEPENDS ${LCOV_REPORT_PATH}
    )

    add_custom_command(
        OUTPUT ${LCOV_HTML_PATH}/index.html
        COMMAND ${GENHTML_BIN} -o ${LCOV_HTML_PATH} ${LCOV_REPORT_PATH} --demangle-cpp
        DEPENDS ${GEMHTML_BIN} ${LCOV_REPORT_PATH}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating lcov html report"
    )

    add_custom_target(coverage-lcov
        DEPENDS ${LCOV_HTML_PATH}/index.html
    )

    add_dependencies(coverage-lcov coverage-lcov-info)
endfunction()