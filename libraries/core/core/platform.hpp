#ifndef MORPHEUS_PLATFORM_H
#define MORPHEUS_PLATFORM_H

// clang-format off
//---------------------------------------------------------------------------------------------------------------------
#include <cstdint>
#include <core/morpheuscore_export.h>

    /*! @defgroup Compiler
            The compiler group of macros allow for compile time detection of the current compiler
            and version.
        @{
    */

    #if !defined ( MORPHEUS_COMPILER )

        /*! @def MORPHEUS_MWERKS_COMPILER
                This token is used to signify the use of the Clang compiler.
         */
        #define MORPHEUS_CLANG_COMPILER             1

        /*! @def MORPHEUS_GNUC_COMPILER
                This token is used to signify the use of the GNUC C++ compiler.
         */
        #define MORPHEUS_GNUC_COMPILER              2

        /*! @def MORPHEUS_ICL_COMPILER
                This token is used to signify the use of the Intel C++ compiler.
         */
        #define MORPHEUS_ICL_COMPILER               3

        /*! @def MORPHEUS_VISUALSTUDIO_COMPILER
                This token is used to signify the use of the Microsoft's C++ compiler. Only version
                including and beyond Visual Studio 2017 are supported.
         */
        #define MORPHEUS_VISUALSTUDIO_COMPILER      4

        /*! @def MORPHEUS_UNKNOWN_COMPILER
                This token is used to signify the use of the current compiler is unknown and as
                such is not supported.
         */
        #define MORPHEUS_UNKNOWN_COMPILER           5


        /*! @def MORPHEUS_COMPILER_VERSION_NUMBER
                This is a macro which can be used to generate a compiler number composed of the
                major, minor and patch number of the compiler.
         */
        #define MORPHEUS_COMPILER_VERSION_NUMBER( major, minor, patch ) \
            ( ( (major) * 10000000 ) + ( (minor) * 100000 ) + ( patch ) )


        /*! @def    MORPHEUS_COMPILER
                This token is used project wide to detect the current compiler being used to build
                the code base.

            @def    MORPHEUS_COMP_VER
                This token is used to numerate the version of the current current complier
                (denoted by MORPHEUS_COMPILER)
         */
        #if defined ( __clang__ )

            #define MORPHEUS_COMPILER   MORPHEUS_CLANG_COMPILER
            #define MORPHEUS_COMP_VER   MORPHEUS_COMPILER_VERSION_NUMBER(__clang_major__,    \
                                                                         __clang_minor__,    \
                                                                         __clang_patchlevel__)

        #elif defined ( __GNUC__ )

            #define MORPHEUS_COMPILER   MORPHEUS_GNUC_COMPILER
            #define MORPHEUS_COMP_VER   MORPHEUS_COMPILER_VERSION_NUMBER(__GNUC__,         \
                                                                        __GNUC_MINOR__,    \
                                                                        __GNUC_PATCHLEVEL__)

        #elif defined ( __INTEL_COMPILER )

            #define MORPHEUS_COMPILER   MORPHEUS_ICL_COMPILER
            #define MORPHEUS_COMP_VER   __ICL

            #if defined ( _MSC_VER )
                #define MORPHEUS_INTEL_COMPILER_FOR_WINDOWS 1
                #define MORPHEUS_INTEL_COMPILER_FOR_LINUX 0
            #else
                #define MORPHEUS_INTEL_COMPILER_FOR_WINDOWS 0
                #define MORPHEUS_INTEL_COMPILER_FOR_LINUX 1
            #endif

        #elif defined ( _MSC_VER )

            #define MORPHEUS_COMPILER   MORPHEUS_VISUALSTUDIO_COMPILER
            #define MORPHEUS_COMP_VER   _MSC_VER

        #else

            #define MORPHEUS_COMPILER   MORPHEUS_UNKNOWN_COMPILER
            #define MORPHEUS_COMP_VER   0

        #endif

        /*! @def MORPHEUS_IS_GCC_COMPATIBLE_COMPILER
                This is a macro which can be used to with proprocessor directives to conditionally
                compile code paths if the current compiler is compatible with the settings of the
                GCC compiler.
         */
        #define MORPHEUS_IS_GCC_COMPATIBLE_COMPILER \
                    (MORPHEUS_COMPILER == MORPHEUS_GNUC_COMPILER)  || \
                    (MORPHEUS_COMPILER == MORPHEUS_CLANG_COMPILER) || \
                    (MORPHEUS_INTEL_COMPILER_FOR_LINUX)

        /*! @def MORPHEUS_IS_GCC_VISUALSTUDIO_COMPILER
                This is a macro which can be used to with proprocessor directives to conditionally
                compile code paths if the current compiler is compatible with the settings of the
                Visual Studio compiler.
         */
        #define MORPHEUS_IS_VISUALSTUDIO_COMPILER \
                    (MORPHEUS_COMPILER == MORPHEUS_VISUALSTUDIO_COMPILER)  || \
                    (MORPHEUS_INTEL_COMPILER_FOR_WINDOWS)

    #endif // !defined ( MORPHEUS_COMPILER )
    /*! @} */



    /*! @defgroup Platform
            The platform group of macros allow for compile time detection of the current platform.
        @{
    */
    #if !defined ( MORPHEUS_BUILD_PLATFORM )

        /*! @def MORPHEUS_TARGET_PLATFORM_WINDOWS
                This token is used to signify the Microsoft Windows PC platform.
         */
        #define MORPHEUS_TARGET_PLATFORM_PC_WINDOWS          1001

        /*! @def MORPHEUS_TARGET_PLATFORM_APPLE
                This token is used to signify the Apple Macintosh PC platform.
         */
        #define MORPHEUS_TARGET_PLATFORM_APPLE               1002

        /*!	@def MORPHEUS_TARGET_PLATFORM_LINUX
                This token is used to signify the Linux PC platform.
         */
        #define MORPHEUS_TARGET_PLATFORM_LINUX               1003

        #if ( defined ( __WIN32__ ) || defined ( _WIN32 ) || defined ( WIN32 ) || defined ( _WIN64 ) )

            #define MORPHEUS_BUILD_PLATFORM	MORPHEUS_TARGET_PLATFORM_PC_WINDOWS

        #elif defined ( __APPLE_CC__)

            #define MORPHEUS_BUILD_PLATFORM	MORPHEUS_TARGET_PLATFORM_APPLE

        #elif defined ( __linux )

            #define MORPHEUS_BUILD_PLATFORM	MORPHEUS_TARGET_PLATFORM_LINUX

        #else

            #define MORPHEUS_BUILD_PLATFORM
            #error "Platform is not currently supported, MORPHEUS libraries will not compile!"

        #endif
    #endif
    /*! @} */

//---------------------------------------------------------------------------------------------------------------------
// clang-format on

#endif // MORPHEUS_PLATFORM_H
