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
include(CheckCXXCompilerFlag)

option(ENABLE_CODE_COVERAGE "Enable code coverage" OFF)


set(COVERAGE_SUPPORTED_FLAGS
    # gcc 8 onwards
    "-fprofile-arcs -fprofile-abs-path -ftest-coverage"

    # gcc and clang
    "-fprofile-arcs -ftest-coverage"

    # gcc and clang fallback
    "--coverage"
)



#[=======================================================================[.rst:
coverage_target_clean_intermediate_file
------------------

Overview
^^^^^^^^

#]=======================================================================]
function(coverage_target_clean_intermediate_file)
    set(options QUIET)
    set(oneValueArgs TARGET_NAME RETURN_NOTE_FILES RETURN_DATA_FILES)
    set(multiValueArgs)
    cmake_parse_arguments(COVERAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT COVERAGE_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME parameter must be supplied")
    endif()

#    get_target_property(TARGET_SOURCES ${COVERAGE_TARGET_NAME} SOURCES)
    targets_get_translation_units(TARGET ${COVERAGE_TARGET_NAME} RESULT targetSources)

    #foreach (file IN LISTS EXPECTED_FILES)
    #    targets_relative_path_of_source(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT file SOURCE_FILE ${file})
    #    set(INTERMEDIATE_FILE "CMakeFiles/${COVERAGE_TARGET_NAME}.dir/${file}")
    #    list(APPEND CLEAN_FILES INTERMEDIATE_FILE)
    #endforeach()

#[[    foreach(file IN LISTS targetSources)
        targets_relative_path_of_source(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT translationFile SOURCE_FILE ${file})
        set(translationUnitLocation "CMakeFiles/${COVERAGE_TARGET_NAME}.dir/${translationFile}")
        message(STATUS "${file} in translation unit space is ${translationFile} and final location is ${translationUnitLocation}")
        list(APPEND targetTranslationUnitLocations ${translationUnitLocation})
    endforeach()
    message(STATUS "targetTranslationUnitLocations is ${targetTranslationUnitLocations}")
]]

    foreach (file IN LISTS targetSources)
        list(APPEND gcovNoteFiles "${file}.gcno")
        list(APPEND gcovDataFiles "${file}.gcda")
    endforeach()

    string(REPLACE ";" "\n" gcovNoteFilesList "${gcovNoteFiles}")
    message(STATUS "gcovNoteFiles is ${gcovNoteFilesList}")
#    message(STATUS "gcovNoteFiles is ${gcovNoteFiles}")

    string(REPLACE ";" "\n" gcovDataFilesList "${gcovDataFiles}")
    message(STATUS "gcovDataFiles is ${gcovDataFilesList}")
#    message(STATUS "gcovDataFiles is ${gcovDataFiles}")

#    set(EXPECTED_FILES "${gcovNoteFiles}" "${gcovDataFiles}")
#    foreach (file IN LISTS EXPECTED_FILES)
#        targets_relative_path_of_source(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT file SOURCE_FILE ${file})
#        set(INTERMEDIATE_FILE "CMakeFiles/${COVERAGE_TARGET_NAME}.dir/${file}")
#        list(APPEND CLEAN_FILES INTERMEDIATE_FILE)
#    endforeach()

    set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${gcovNoteFiles} ${gcovDataFiles}")

    if(COVERAGE_RETURN_NOTE_FILES)
        set(${COVERAGE_RETURN_NOTE_FILES} "${gcovNoteFiles}" PARENT_SCOPE)
    endif()
    if(COVERAGE_RETURN_DATA_FILES)
        set(${COVERAGE_RETURN_DATA_FILES} "${gcovDataFiles}" PARENT_SCOPE)

        #[[
        foreach(cppExt IN LISTS CMAKE_CXX_SOURCE_FILE_EXTENSIONS)
            #message("GCov Data files for ${COVERAGE_TARGET_NAME}: ${gcovDataFiles}")
            #string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" cppExt ".*\.${cppExt}\.gcda")
            #set(cppExt ".*\\.${cppExt}\\.gcda$")
            #message("Regex is ${cppExt}")
            #string(REGEX MATCH ".*\\.${cppExt}\\.gcda$" CXX_GCOV_DATA_FILES ${gcovDataFiles})

            #message("Filters by string GCov Data files for ${COVERAGE_TARGET_NAME} to: ${CXX_GCOV_DATA_FILES}")

            set(filteredGcovDataFiles "${gcovDataFiles}")
            #string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" cppExt "${cppExt}\.gcda")
            string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" cppExt "${cppExt}") # Escape any file extensions with special characters.
            list(FILTER filteredGcovDataFiles INCLUDE REGEX ".*\\.${cppExt}\\.gcda$")
            #message("Filters by list GCov Data files for ${COVERAGE_TARGET_NAME} to: ${GCOV_DATA_FILES_COPY}")

            list(APPEND remainingGcovDataFiles ${filteredGcovDataFiles})
        endforeach()
        message("Setting GCov Data files for ${COVERAGE_TARGET_NAME} to: ${COVERAGE_RETURN_DATA_FILES} containing ${remainingGcovDataFiles}")

        set(${COVERAGE_RETURN_DATA_FILES} "${remainingGcovDataFiles}" PARENT_SCOPE)
        ]]
        #message("GCov Data files for ${COVERAGE_TARGET_NAME}: ${${COVERAGE_RETURN_DATA_FILES}}")
    endif()

endfunction()



function(enable_code_coverage)
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
    set(COVERAGE_LCOV_TO_COBERTURA_BIN ${COVERAGE_VENV}/bin/lcov_cobertura)
    virtualenv_create(
        DESTINATION ${COVERAGE_VENV}
        REQUIREMENTS ${PROJECT_SOURCE_DIR}/cmake/requirements/coverage_requirements.txt
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        OUTPUT
            ${COVERAGE_FASTCOV_BIN}
            ${COVERAGE_FASTCOV_TO_SONARQUBE_BIN}
            ${COVERAGE_LCOV_TO_COBERTURA_BIN}
    )

    set(COVERAGE_REPORT_DIR "${CMAKE_BINARY_DIR}/coverage")
    set(COVERAGE_REPORT_PATH "${COVERAGE_REPORT_DIR}/fastcov_report.json")
    set(SONARQUBE_REPORT_PATH "${COVERAGE_REPORT_DIR}/sonarcube_coverage.xml")
    set(COBERTURA_REPORT_PATH "${COVERAGE_REPORT_DIR}/cobertura_coverage.xml")
    set(LCOV_REPORT_PATH "${COVERAGE_REPORT_DIR}/lcov.info")
    set(LCOV_HTML_PATH "${COVERAGE_REPORT_DIR}/html")

#    string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" ROOT_SEARCH_DIR "${CMAKE_BINARY_DIR}")
#    message(STATUS "ROOT_SEARCH_DIR: ${ROOT_SEARCH_DIR}")
    
    if (NOT TARGET CodeCoverage)
        add_library(CodeCoverage INTERFACE)
        add_library(coverage::coverage ALIAS CodeCoverage)

        foreach (FLAGS ${COVERAGE_SUPPORTED_FLAGS})
            set(CMAKE_REQUIRED_FLAGS "${FLAGS}")
            check_cxx_compiler_flag("${FLAGS}" COVERAGE_FLAGS_DETECTED)

            if (COVERAGE_FLAGS_DETECTED)
                string(REPLACE " " ";" FLAGS "${FLAGS}")
                set(COVERAGE_COMPILER_FLAGS "${FLAGS}" CACHE STRING "${CMAKE_CXX_COMPILER_ID} flags for code coverage.")
                mark_as_advanced(COVERAGE_COMPILER_FLAGS)
                break()
            else ()
                message(WARNING "Code coverage is not available for the currently enable compiler ${CMAKE_CXX_COMPILER_ID} via the compiler flags ${FLAGS}.")
            endif ()
        endforeach()

        target_compile_options(CodeCoverage INTERFACE ${COVERAGE_COMPILER_FLAGS})
        target_link_options(CodeCoverage INTERFACE ${COVERAGE_COMPILER_FLAGS})
    endif()

    targets_get_all(RESULT allTargets DIRECTORY ${PROJECT_SOURCE_DIR})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: All project targets: ${allTargets}")
    endif()
    
    targets_filter_for_sources(RESULT targetsWithSource TARGETS ${allTargets})
    if (COVERAGE_VERBOSE)
        message(STATUS "Coverage: Targets with sources: ${targetsWithSource}}")
    endif()

    foreach(target IN LISTS targetsWithSource)
        target_link_libraries(${target} PUBLIC coverage::coverage)
        coverage_target_clean_intermediate_file(TARGET_NAME ${target} RETURN_DATA_FILES outputGCovDataFile)

        foreach(gcdaFile IN LISTS outputGCovDataFile)
            cmake_path(GET gcdaFile STEM LAST_ONLY translationUnitFile)
            get_filename_component(translationUnitDir "${gcdaFile}" DIRECTORY)
            set(translationUnit "${translationUnitDir}/${translationUnitFile}")
 
            set(objectFile "${translationUnit}.o")
            add_custom_command(OUTPUT "${translationUnit}.gcno"
			    COMMAND ${CMAKE_COMMAND} -E touch "${translationUnit}.gcno"
                DEPENDS "${objectFile}"
		    )
            add_custom_command(OUTPUT ${gcdaFile}
			    COMMAND ${CMAKE_COMMAND} -E touch "${gcdaFile}"
                DEPENDS "${translationUnit}.gcno"
		    )
        endforeach()
        add_custom_target(${target}-gcda-init DEPENDS ${outputGCovDataFile})

        list(APPEND gcdaInitTargets ${target}-gcda-init)
        list(APPEND allGcovDataFiles ${outputGCovDataFile})
        message("GCov Data files for ${target}: ${outputGCovDataFile}")
    endforeach()

    list(REMOVE_DUPLICATES allGcovDataFiles)

    message("GCov Data files: ${allGcovDataFiles}")
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
            ${gcdaInitTargets}
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
            ${allGcovDataFiles}
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

    add_custom_command(
        OUTPUT ${COBERTURA_REPORT_PATH}
        COMMAND
            ${COVERAGE_LCOV_TO_COBERTURA_BIN} ${LCOV_REPORT_PATH}#
                --base-dir ${PROJECT_SOURCE_DIR}
                --output ${COBERTURA_REPORT_PATH}
                --demangle
        DEPENDS
            ${LCOV_REPORT_PATH}
            ${COVERAGE_LCOV_TO_COBERTURA_BIN}
        WORKING_DIRECTORY
            ${CMAKE_BINARY_DIR}
        COMMENT
            "Generate Cobertura XML report from LCov report"
    )

    add_custom_target(coverage-cobertura
        DEPENDS ${COBERTURA_REPORT_PATH}
    )

endfunction()