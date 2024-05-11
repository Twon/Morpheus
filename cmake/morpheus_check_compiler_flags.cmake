include_guard(GLOBAL)

cmake_minimum_required(VERSION 3.25)

#[=======================================================================[.rst:
morpheus_check_compiler_flag
------------------

Overview
^^^^^^^^

Checks for the given compiler if the given flag is supported for the specified languages
if CMake provides a compiler check module for the underlying language.

.. code-block:: cmake

  morpheus_check_compiler_flag(
      [FLAG <flag>]
      [LANGUAGE <langauge>]
      [RESULT <result>]
  )
   -- Confirms support for the compile flag across enabled languages.

  ``FLAG``
    The ``FLAG`` compiler flag to test if is supported for the specified language.

  ``RESULT``
    The ``RESULT`` option is required to store the result of the function.  TRUE if
    there is compiler support for the feature.

#]=======================================================================]
function(morpheus_check_compiler_flag)
    set(options)
    set(oneValueArgs FLAG LANGUAGE RESULT)
    set(multiValueArgs)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT MORPHEUS_FLAG)
        message(FATAL_ERROR "FLAG parameter must be supplied")
    endif()
    if (NOT MORPHEUS_LANGUAGE)
        message(FATAL_ERROR "LANGUAGE parameter must be supplied")
    endif()
     if (NOT MORPHEUS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()

    if (${MORPHEUS_LANGUAGE} STREQUAL "C")
        include(CheckCCompilerFlag)
        check_c_compiler_flag("${MORPHEUS_FLAG}" ${MORPHEUS_RESULT})
    elseif (${MORPHEUS_LANGUAGE} STREQUAL "CXX")
        include(CheckCXXCompilerFlag)
        check_cxx_compiler_flag("${MORPHEUS_FLAG}" ${MORPHEUS_RESULT})
    elseif (${MORPHEUS_LANGUAGE} STREQUAL "Fortran")
        include(CheckFortranCompilerFlag)
        check_fortran_compiler_flag("${MORPHEUS_FLAG}" ${MORPHEUS_RESULT})
    elseif (${MORPHEUS_LANGUAGE} STREQUAL "OBJC")
        include(CheckOBJCCompilerFlag)
        check_objc_compiler_flag("${MORPHEUS_FLAG}" ${MORPHEUS_RESULT})
    elseif (${MORPHEUS_LANGUAGE} STREQUAL "OBJCXX")
        include(CheckOBJCXXCompilerFlag)
        check_objcxx_compiler_flag("${MORPHEUS_FLAG}" ${MORPHEUS_RESULT})
    else()
        set(${MORPHEUS_RESULT} FALSE)
        return(PROPAGATE ${MORPHEUS_RESULT})
    endif()
endfunction()


#[=======================================================================[.rst:
morpheus_check_compiler_flags
------------------

Overview
^^^^^^^^

Checks for the given compile supported of the given flags across all languages in
use which have compiler check modules provides in CMake.

.. code-block:: cmake

  morpheus_check_compiler_flags(
      [QUIET]
      [FLAGS <flags>]
      [RESULT <result>]
  )
   -- Confirms support for compiler flags across enabled languages.

  ``RESULT``
    The ``RESULT`` option is required to store the results of the function.  TRUE if
    there is compiler support for the feature.

  ``FLAGS``
    The ``FLAGS`` compiler flags to test if are supported for the enabled languages.

#]=======================================================================]
function(morpheus_check_compiler_flags)
    set(options QUIET)
    set(oneValueArgs NAME PREFIX RESULT)
    set(multiValueArgs FLAGS)
    cmake_parse_arguments(MORPHEUS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (NOT MORPHEUS_NAME)
        message(FATAL_ERROR "NAME parameter must be supplied")
    endif()
    if (NOT MORPHEUS_PREFIX)
        message(FATAL_ERROR "PREFIX parameter must be supplied")
    endif()
    if (NOT MORPHEUS_RESULT)
        message(FATAL_ERROR "RESULT parameter must be supplied")
    endif()
    if (NOT MORPHEUS_FLAGS)
        message(FATAL_ERROR "FLAGS parameter must be supplied")
    endif()

    get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)

    foreach(language IN LISTS languages)
        
        set(COMPILER ${CMAKE_${language}_COMPILER_ID})
        if (${MORPHEUS_PREFIX}_${COMPILER}_FLAGS)
            continue()
        endif()

        foreach(flags IN LISTS MORPHEUS_FLAGS)
            if (NOT MORPHEUS_QUIET)
                message(STATUS "Try ${COMPILER} ${MORPHEUS_NAME} flag = [${flags}]")
            endif()

            set(CMAKE_REQUIRED_FLAGS "${flags}")
            unset(flagsSupported CACHE)
            morpheus_check_compiler_flag(FLAG "${flags}" LANGUAGE ${language} RESULT flagsSupported)
            
            if (flagsSupported)
                set(${MORPHEUS_PREFIX}_${COMPILER}_FLAGS "${flags}" CACHE STRING  "${MORPHEUS_NAME} flags for ${COMPILER} compiler.")
                mark_as_advanced(${MORPHEUS_PREFIX}_${COMPILER}_FLAGS)
                break()
            endif()
        endforeach()

        if (NOT ${flagsSupported})
            set(${MORPHEUS_PREFIX}_${COMPILER}_FLAGS "" CACHE STRING  "${MORPHEUS_NAME} flags for ${COMPILER} compiler.")
            mark_as_advanced(${MORPHEUS_PREFIX}_${COMPILER}_FLAGS)
            message(WARNING "${MORPHEUS_NAME} is not available for ${COMPILER} compiler. Targets using "
                            "this compiler will be compiled without ${MORPHEUS_NAME}.")
        endif()
    endforeach()

    set(${MORPHEUS_RESULT} FALSE)
    return(PROPAGATE ${MORPHEUS_RESULT})

endfunction()
