#pragma once

#define _SGOL_FORCE_INLINE
#include "sgol.h"

namespace sgol {

	template<typename Type>
	class vector
	{
	public:
		_SGOL_INLINE _SGOL_EXPLICIT vector(size_t size)
			: m_Size(size)
		{
			m_Data = new Type[size];
		}

		~vector()
		{
			delete[] m_Data;
			m_Data = nullptr;
			m_Size = 0;
		}

		_SGOL_INLINE Type& _SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL Data() { return m_Data; }

		_SGOL_INLINE size_t _SGOL_FASTCALL Size() { return m_Size; }
	private:
		
	private:
		size_t m_Size;
		Type* m_Data;
	};
}