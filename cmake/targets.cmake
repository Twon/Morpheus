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

#[=======================================================================[.rst:
targets_get_all
------------------

Overview
^^^^^^^^

Locates all targets with in a directory and its subdirectories.


#]=======================================================================]
function(targets_get_all)
    set(options)
    set(oneValueArgs RESULT DIRECTORY)
    set(multiValueArgs)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT ARGS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()
    if (NOT ARGS_DIRECTORY)
        message(FATAL_ERROR "DIRECTORY parameter must be supplied")
    endif()

    get_property(subdirs DIRECTORY ${ARGS_DIRECTORY} PROPERTY SUBDIRECTORIES)
    foreach(subdir IN LISTS subdirs)
        targets_get_all(RESULT subTargets DIRECTORY ${subdir})
    endforeach()

    get_directory_property(allTargets DIRECTORY ${ARGS_DIRECTORY} BUILDSYSTEM_TARGETS)
    set(${ARGS_RESULT} ${subTargets} ${allTargets} PARENT_SCOPE)
endfunction()

#[=======================================================================[.rst:
targets_filter_for_sources
------------------

Overview
^^^^^^^^

Given a list of targets will return a list of targets containing sources to be
compiled.

#]=======================================================================]
function(targets_filter_for_sources)
    set(options)
    set(oneValueArgs RESULT)
    set(multiValueArgs TARGETS)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT ARGS_TARGETS)
        message(FATAL_ERROR "TARGETS parameter must be supplied")
    endif()
    if (NOT ARGS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    foreach(target IN LISTS ARGS_TARGETS)
        get_target_property(TARGET_SOURCES ${target} SOURCES)
        if (NOT TARGET_SOURCES)
            continue()
        endif()

        list(APPEND targets ${target})
    endforeach()
    set(${ARGS_RESULT} ${${ARGS_RESULT}} ${targets} PARENT_SCOPE)

endfunction()


#[=======================================================================[.rst:
targets_get_translation_units
------------------

Overview
^^^^^^^^

Given a target return only source files which result in translation unit
being generated (i.e. no header files).

#]=======================================================================]
function(targets_get_translation_units)
    set(options)
    set(oneValueArgs TARGET RESULT)
    set(multiValueArgs)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT ARGS_TARGET)
        message(FATAL_ERROR "TARGET parameter must be supplied")
    endif()
    if (NOT ARGS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    get_target_property(targetSource ${ARGS_TARGET} SOURCES)

    # CMAKE_CXX_SOURCE_FILE_EXTENSIONS defined in: https://github.com/Kitware/CMake/blob/master/Modules/CMakeCXXCompiler.cmake.in
    foreach(cppExt IN LISTS CMAKE_CXX_SOURCE_FILE_EXTENSIONS)
        # Filter on a copy of the oringal source list
        set(filteredTargetSource "${targetSource}")
        # Escape any file extensions with special characters.
        string(REGEX REPLACE "([][+.*()^])" "\\\\\\1" cppExt "${cppExt}")
        list(FILTER filteredTargetSource INCLUDE REGEX ".*\\.${cppExt}$")
        list(APPEND targetTranslationUnits ${filteredTargetSource})
    endforeach()
#    set(${ARGS_RESULT} ${targetTranslationUnits} PARENT_SCOPE)

    get_target_property(targetBinaryDir ${ARGS_TARGET} BINARY_DIR)
    foreach(file IN LISTS targetTranslationUnits)
        targets_relative_path_of_source(TARGET_NAME ${COVERAGE_TARGET_NAME} RESULT file SOURCE_FILE ${file})
        set(translationUnitLocation "${targetBinaryDir}/CMakeFiles/${COVERAGE_TARGET_NAME}.dir/${file}")
        list(APPEND targetTranslationUnitLocations ${translationUnitLocation})
    endforeach()

    set(${ARGS_RESULT} ${targetTranslationUnitLocations} PARENT_SCOPE)

endfunction()


#[=======================================================================[.rst:
targets_relative_path_of_source
------------------

Overview
^^^^^^^^

#]=======================================================================]
function (targets_relative_path_of_source)
    set(options)
    set(oneValueArgs TARGET_NAME RESULT SOURCE_FILE)
    set(multiValueArgs)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if (NOT ARGS_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME parameter must be supplied")
    endif()
    if (NOT ARGS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    get_target_property(targetSrcDir ${ARGS_TARGET_NAME} SOURCE_DIR)
    get_target_property(targetBinaryDir ${ARGS_TARGET_NAME} BINARY_DIR)

    # Generated files should be in the subdirectories of the targets binary directory
    string(REPLACE "${targetBinaryDir}/" "" file "${ARGS_SOURCE_FILE}")

	if(IS_ABSOLUTE ${file})
		file(RELATIVE_PATH file ${targetSrcDir} ${file})
 	endif()

	# get the right path for file
	string(REPLACE ".." "__" PATH "${file}")
#    if (NOT PATH STREQUAL ${file})
#        message(SEND_ERROR "TARGET_BINARY_DIR is ${TARGET_BINARY_DIR}")
#        message(SEND_ERROR "PATH is ${PATH}")
#        message(SEND_ERROR "file is ${file}")
#    endif()

	set(${ARGS_RESULT} "${PATH}" PARENT_SCOPE)
endfunction()