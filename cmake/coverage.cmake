#[[
Copyright 2022 Antony Peacock

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
]]

include_guard(GLOBAL)

include(targets)
include(virtualenv)

option(ENABLE_CODE_COVERAGE "Enable code coverage" OFF)


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
        targets_relative_path_of_source(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT file SOURCE_FILE ${file})
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
    virtualenv_create(
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

    targets_get_all(RESULT allTargets DIRECTORY ${PROJECT_SOURCE_DIR})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: All project targets: ${allTargets}")
    endif()
    
    targets_filter_for_sources(RESULT targetsWithSource TARGETS ${allTargets})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: Targets with sources: ${targetsWithSource}}")
    endif()
    
    foreach(target IN LISTS targetsWithSource)
#        get_target_property(TARGET_TYPE ${target} TYPE)
#        message("Registering properties for target: ${target}:${TARGET_TYPE}")
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