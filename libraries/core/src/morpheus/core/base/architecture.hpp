#pragma once

/// @def MORPHEUS_PLATFORM_ARCHITECTURE
///		Id for the currently target architecture
#if !defined(MORPHEUS_PLATFORM_ARCHITECTURE)

    /// @def MORPHEUS_TARGET_ARCHITECTURE_X86
    ///		This token is used to signify the processor architecture is X86
    #define MORPHEUS_TARGET_ARCHITECTURE_X86     1

    /// @def MORPHEUS_TARGET_ARCHITECTURE_X64
    ///		This token is used to signify the processor architecture is 64-bit X86 otherwise
    ///		know as X64.
    #define MORPHEUS_TARGET_ARCHITECTURE_X64     2

    /// @def MORPHEUS_TARGET_ARCHITECTURE_POWERPC
    ///	This token is used to signify the processor architecture is PowerPC.
    #define MORPHEUS_TARGET_ARCHITECTURE_POWERPC 3

    ///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM_4
    ///	This token is used to signify the processor architecture is ARM arch 4
    #define MORPHEUS_TARGET_ARCHITECTURE_ARM_4   4

    ///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM_5
    ///	This token is used to signify the processor architecture is ARM arch 5
    #define MORPHEUS_TARGET_ARCHITECTURE_ARM_5   5

    ///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM_6
    ///	This token is used to signify the processor architecture is ARM arch 6
    #define MORPHEUS_TARGET_ARCHITECTURE_ARM_6   6

    ///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM_7
    ///	This token is used to signify the processor architecture is ARM arch 7
    #define MORPHEUS_TARGET_ARCHITECTURE_ARM_7   7

    ///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM_8
    ///	This token is used to signify the processor architecture is ARM arch 8
    #define MORPHEUS_TARGET_ARCHITECTURE_ARM_8   8

    /// @def MORPHEUS_TARGET_ARCHITECTURE_MIPS
    ///    This token is used to signify the processor architecture is MIPS
    #define MORPHEUS_TARGET_ARCHITECTURE_MIPS    9

    #if defined(__X86__) || defined(_X86_) || defined(_M_IX86)

        #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_X86

    #elif defined(__x86_64__) || defined(_M_X64)

        #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_X64

    #elif defined(_M_PPC) || defined(M_MPPC)

        #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_POWERPC

    #elif defined(__arm__) || defined(__arm64) || defined(_M_ARM) || defined(_M_ARM64) || defined(__TARGET_ARCH_ARM)

        #if defined(__ARM_ARCH_8__) || defined(__ARM_ARCH_8A__) || defined(__aarch64__) || (defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM - 0 >= 8)

            #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_ARM_8

        #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || \
           (defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM - 0 >= 7)

            #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_ARM_7

        #elif defined(__ARM_ARCH_6__)  || defined(__ARM_ARCH_6J__)  || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6Z__) || \
              defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6M__)  || \
             (defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM - 0 >= 6)

            #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_ARM_6

        #elif defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__) || (defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM - 0 >= 5)

            #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_ARM_5

        #elif defined(__ARM_ARCH_4__) || defined(__ARM_ARCH_4T__) || (defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM - 0 >= 4)

            #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_ARM_4

        #else

            #error "ARM Architecture is not currently supported, Morpheus libraries will not compile!"

        #endif

    #elif defined(__mips__) || defined(__mips) || defined(__MIPS__)

        #define MORPHEUS_PLATFORM_ARCHITECTURE MORPHEUS_TARGET_ARCHITECTURE_MIPS

    #else

        #define MORPHEUS_PLATFORM_ARCHITECTURE
        #error "Architecture is not currently supported, Morpheus libraries will not compile!"

    #endif

#endif // !defined (  MORPHEUS_PLATFORM_ARCHITECTURE )
