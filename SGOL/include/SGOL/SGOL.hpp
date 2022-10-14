#pragma once

#define __SGOL_ENABLE_ALL

#ifdef __SGOL_ENABLE_ALL
	#define __SGOL_HAS_FASTCALL
	#define __SGOL_HAS_INLINE
	#define __SGOL_FORCEINLINE
	#define __SGOL_HAS_NODISCARD
#endif // __SGOL_ENABLE_ALL

#ifdef __SGOL_HAS_FASTCALL
	#define __SGOL_FASTCALL __fastcall
#else
	#define __SGOL_FASTCALL
#endif //__SGOL_HAS_FASTCALL

#ifdef __SGOL_HAS_INLINE
	#ifdef __SGOL_FORCEINLINE
		#define __SGOL_INLINE __forceinline
	#else
		#define __SGOL_INLINE inline
	#endif
#else
	#define __SGOL_INLINE
#endif //__SGOL_HAS_INLINE

#ifdef __SGOL_HAS_NODISCARD
	#define __SGOL_NODISCARD [[nodiscard]]
#else
	#define __SGOL_NODISCARD
#endif // __SGOL_HAS_NODISCARD

#ifdef __SGOL_ENABLE_ALL
	#undef __SGOL_HAS_FASTCALL
	#undef __SGOL_HAS_INLINE
	#undef __SGOL_FORCEINLINE
	#undef __SGOL_HAS_NODISCARD
#endif // __SGOL_HAS_NODISCARD

#ifdef __SGOL_ENABLE_MEM_TRACKER
#undef __SGOL_ENABLE_MEM_TRACKER

#include <iostream>

struct MemUse
{
	size_t TotalAllocation = 0;
	size_t TotalDeletion = 0;

	inline size_t GetCurrentAllocation() const { return TotalAllocation - TotalDeletion; }

};

static MemUse g_MemUse;

#include <stdlib.h>
void* operator new(size_t size)
{
	g_MemUse.TotalAllocation += size;
	return malloc(size);
}

void operator delete(void* address, size_t size)
{
	g_MemUse.TotalDeletion += size;
	free(address);
}

std::ostream& operator<< (std::ostream& stream, const MemUse& memUse)
{
	stream << "MemUse Table:----------------------------------------------------" << std::endl;
	stream << "\tTotal Allocations: " << memUse.TotalAllocation << " Bytes" << std::endl;
	stream << "\tTotal Deletions: " << memUse.TotalDeletion << " Bytes" << std::endl;
	stream << "\tCurrent Allocations: " << memUse.GetCurrentAllocation() << " Bytes" << std::endl;
	stream << "-----------------------------------------------------------------" << std::endl;
	return stream;
}
#endif // __SGOL_ENABLE_MEM_TRACKER

#include <type_traits>

namespace SGOL {
	template<bool enable, typename T = void>
	struct EnableIf {};

	template<typename T>
	struct EnableIf<true, T> {
		using Type = T;
	};

	template<typename T, T val>
	struct IntegralConstant
	{
		static constexpr T s_Value = val;

		using ValueType = T;
		using Type      = IntegralConstant;

		constexpr operator ValueType() const noexcept
		{
			return s_Value;
		}

		__SGOL_NODISCARD constexpr ValueType operator()() const noexcept
		{
			return s_Value;
		}

	};

	template<bool Value>
	using BoolConstant = IntegralConstant<bool, Value>;

	using TrueType  = BoolConstant<true>;
	using FalseType = BoolConstant<false>;

	template<typename From, typename To>
	struct IsConvertable : BoolConstant<std::is_convertible_v<From, To>> {

	};
}