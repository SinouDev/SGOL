#pragma once

#if 0
#define _SGOL_NO_MACRO

#if 0
#define _SGOL_NO_INLINE
#define _SGOL_NO_FASTCALL
#define _SGOL_NO_EXPLICIT
#define _SGOL_NO_CONSTEXPR
#endif

#endif // _SGOL_NO_MACRO

#if !defined(_SGOL_NO_MACRO)
	#if !defined(_SGOL_NO_INLINE)
		#if defined(_SGOL_FORCE_INLINE)
			#define _SGOL_INLINE __forceinline
		#else
			#define _SGOL_INLINE inline
		#endif // _SGOL_FORCE_INLINE
	#else
		#define _SGOL_INLINE
	#endif // _SGOL_NO_INLINE

	#if !defined(_SGOL_NO_FASTCALL)
		#define _SGOL_FASTCALL __fastcall
	#else
		#define _SGOL_FASTCALL
	#endif // _SGOL_NO_FASTCALL

	#if !defined(_SGOL_NO_NODISCARD)
		#define _SGOL_NODISCARD [[nodiscard]]
	#else
		#define _SGOL_NODISCARD
	#endif // _SGOL_NO_NODISCARD

	#if !defined(_SGOL_NO_EXPLICIT)
		#define _SGOL_EXPLICIT explicit
	#else
		#define _SGOL_EXPLICIT
	#endif // _SGOL_NO_EXPLICIT

	#if !defined(_SGOL_NO_CONSTEXPR)
		#define _SGOL_CONSTEXPR constexpr
	#else
		#define _SGOL_CONSTEXPR
	#endif // _SGOL_NO_CONSTEXPR
#else
	#define _SGOL_INLINE
	#define _SGOL_FASTCALL
	#define _SGOL_NODISCARD
	#define _SGOL_EXPLICIT
	#define _SGOL_CONSTEXPR
#endif // _SGOL_NO_MACRO

#include <cstdint>

namespace sgol {

}