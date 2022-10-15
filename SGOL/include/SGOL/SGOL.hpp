#pragma once

#define __SGOL_ENABLE_ALL

#ifdef __SGOL_ENABLE_ALL
	#define __SGOL_HAS_FASTCALL
	#define __SGOL_HAS_INLINE
	#define __SGOL_FORCEINLINE
	#define __SGOL_HAS_NODISCARD
	#define __SGOL_HAS_EXPLICIT
	#define __SGOL_HAS_CONSTEXPR
	#define __SGOL_HAS_NOEXCEPT
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

#ifdef __SGOL_HAS_EXPLICIT
	#define __SGOL_EXPLICIT explicit
#else
	#define __SGOL_EXPLICIT
#endif // __SGOL_HAS_EXPLICIT

#ifdef __SGOL_HAS_CONSTEXPR
	#define __SGOL_CONSTEXPR constexpr
#else
	#define __SGOL_CONSTEXPR
#endif // __SGOL_HAS_CONSTEXPR

#ifdef __SGOL_HAS_NOEXCEPT
	#define __SGOL_NOEXCEPT noexcept
#else
	#define __SGOL_NOEXCEPT
#endif // __SGOL_HAS_NOEXCEPT

#ifdef __SGOL_ENABLE_ALL
	#undef __SGOL_HAS_FASTCALL
	#undef __SGOL_HAS_INLINE
	#undef __SGOL_FORCEINLINE
	#undef __SGOL_HAS_NODISCARD
	#undef __SGOL_HAS_EXPLICIT
	#undef __SGOL_HAS_CONSTEXPR
	#undef __SGOL_HAS_NOEXCEPT
#endif // __SGOL_HAS_NODISCARD

#undef __SGOL_NO_MACRO

#ifdef __SGOL_ENABLE_MEM_TRACKER
#undef __SGOL_ENABLE_MEM_TRACKER

#include <iostream>

struct MemUse
{

	struct CurrentInUseAllocationInfo
	{
		size_t CurrentInUseAllocationSize = 0;
		size_t CurrentInUseAllocationCount = 0;
	};

	class TotalAllocationDeallocationInfo
	{

	public:

		// This operator method will add to the total allocations size and increment the count by 1
		__SGOL_INLINE TotalAllocationDeallocationInfo& __SGOL_FASTCALL operator<<(size_t value) __SGOL_NOEXCEPT
		{
			m_TotalAllocationSize += value;
			m_TotalAllocationCount++;
			return *this;
		}

		// This operator method will add to the total deallocations size and increment the count by 1
		__SGOL_INLINE TotalAllocationDeallocationInfo& __SGOL_FASTCALL operator>>(size_t value) __SGOL_NOEXCEPT
		{
			m_TotalDeallocationSize += value;
			m_TotalDeallocationCount++;
			return *this;
		}

		// This operator method will add to the total allocations size and increment the count by 1
		__SGOL_INLINE TotalAllocationDeallocationInfo& operator+=(size_t value) __SGOL_NOEXCEPT
		{
			m_TotalAllocationSize += value;
			m_TotalAllocationCount++;
			return *this;
		}

		// This operator method will add to the total deallocations size and increment the count by 1
		__SGOL_INLINE TotalAllocationDeallocationInfo& __SGOL_FASTCALL operator-=(size_t value) __SGOL_NOEXCEPT
		{
			m_TotalDeallocationSize += value;
			m_TotalDeallocationCount++;
			return *this;
		}

		// This operator method will calculate the current allocations size and count
		__SGOL_NODISCARD __SGOL_INLINE CurrentInUseAllocationInfo __SGOL_FASTCALL operator~() const __SGOL_NOEXCEPT
		{
			return {
				m_TotalAllocationSize - m_TotalDeallocationSize,
				m_TotalAllocationCount - m_TotalDeallocationCount
			};
		}

	private:

		friend std::ostream& operator<< (std::ostream&, const MemUse::TotalAllocationDeallocationInfo&);

	private:
		size_t m_TotalAllocationCount = 0;
		size_t m_TotalAllocationSize = 0;
		size_t m_TotalDeallocationCount = 0;
		size_t m_TotalDeallocationSize = 0;

	} TotalAllocationDeallocation;

	__SGOL_NODISCARD __SGOL_INLINE CurrentInUseAllocationInfo __SGOL_FASTCALL GetCurrentAllocation() const __SGOL_NOEXCEPT { return ~TotalAllocationDeallocation; }

};

static MemUse g_MemUse;

#include <stdlib.h>
void* operator new(size_t size)
{
	g_MemUse.TotalAllocationDeallocation << size;
	return malloc(size);
}

void operator delete(void* address, size_t size)
{
	g_MemUse.TotalAllocationDeallocation >> size;
	free(address);
}

std::ostream& operator<< (std::ostream& stream, const MemUse::CurrentInUseAllocationInfo& info)
{
	stream << "\tIn use Allocations: " << info.CurrentInUseAllocationCount << ", size: " << info.CurrentInUseAllocationSize << " Bytes";
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const MemUse::TotalAllocationDeallocationInfo& info)
{
	stream << "\tTotal Allocations: " << info.m_TotalAllocationCount << ", size: " << info.m_TotalAllocationSize << " Bytes" << std::endl;
	stream << "\tTotal Deallocations: " << info.m_TotalDeallocationCount << ", size: " << info.m_TotalDeallocationSize << " Bytes";
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const MemUse& memUse)
{
	stream << "MemUse Table:----------------------------------------------------" << std::endl;
	stream << memUse.TotalAllocationDeallocation << std::endl;
	stream << memUse.GetCurrentAllocation() << std::endl;
	stream << "-----------------------------------------------------------------" << std::endl;
	return stream;
}
#endif // __SGOL_ENABLE_MEM_TRACKER

#include <type_traits>

// ****** Simple Graphic's Optimized Library (SGOL) ******
//   Simple c++ template library just like std template library on c++ but focused more on performanceand graphics applications like Game Engines, Renderersand so on
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