#pragma once

#include "sgol.h"

namespace sgol {

	template<typename Type, size_t size>
	class array
	{
	public:

		_SGOL_INLINE Type& _SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL Data() { return m_Data; }

		_SGOL_CONSTEXPR _SGOL_INLINE size_t _SGOL_FASTCALL Size() { return size; }

	private:
		Type m_Data[size];
	};

}