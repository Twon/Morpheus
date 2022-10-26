#pragma once

/// @def MORPHEUS_PLATFORM_ARCHITECTURE
///		Id for the currently target architecture
#if !defined ( MORPHEUS_PLATFORM_ARCHITECTURE )

	/// @def FREEDOM_TARGET_ARCHITECTURE_X86
	///		This token is used to signify the processor architecture is X86
	#define MORPHEUS_TARGET_ARCHITECTURE_X86				1

	/// @def MORPHEUS_TARGET_ARCHITECTURE_X64
	///		This token is used to signify the processor architecture is 64-bit X86 otherwise
	///		know as X64.
	#define MORPHEUS_TARGET_ARCHITECTURE_X64				2

    /// @def MORPHEUS_TARGET_ARCHITECTURE_POWERPC
    ///	This token is used to signify the processor architecture is	PowerPC.
	#define MORPHEUS_TARGET_ARCHITECTURE_POWERPC			3

	///	@def MORPHEUS_TARGET_ARCHITECTURE_ARM
	///	This token is used to signify the processor architecture is	ARM
	#define MORPHEUS_TARGET_ARCHITECTURE_ARM				4

	/// @def MORPHEUS_TARGET_ARCHITECTURE_MIPS
	///    This token is used to signify the processor architecture is	MIPS
	#define MORPHEUS_TARGET_ARCHITECTURE_MIPS			5

	#if defined ( __X86__ ) || defined ( _X86_ ) || defined ( _M_IX86 )

		#define MORPHEUS_PLATFORM_ARCHITECTURE	MORPHEUS_TARGET_ARCHITECTURE_X86

	#elif defined ( __x86_64__ ) || defined ( _M_X64 )

		#define MORPHEUS_PLATFORM_ARCHITECTURE	MORPHEUS_TARGET_ARCHITECTURE_X64

	#elif defined ( _M_PPC ) || defined ( M_MPPC )

		#define MORPHEUS_PLATFORM_ARCHITECTURE	MORPHEUS_TARGET_ARCHITECTURE_POWERPC

	#else

		#define MORPHEUS_PLATFORM_ARCHITECTURE
		#error "Architecture is not currently supported, Morpheus libraries will not compile!"

	#endif

#endif // !defined (  MORPHEUS_PLATFORM_ARCHITECTURE )
