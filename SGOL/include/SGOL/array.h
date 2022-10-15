#pragma once

#include "SGOL.hpp"

namespace SGOL {

	template<typename Type, size_t size>
	class array
	{
	public:

		__SGOL_INLINE Type& __SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		__SGOL_INLINE const Type& __SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		__SGOL_INLINE Type& __SGOL_FASTCALL Data() { return m_Data; }

		__SGOL_CONSTEXPR __SGOL_INLINE size_t _SGOL_FASTCALL Size() { return size; }

	private:
		Type m_Data[size];
	};

}