#pragma once

#include "sgol.h"

namespace sgol {

	template<typename _Ty>
	class vector2D
	{
		using Type = _Ty;
	private:
		_SGOL_INLINE vector2D()
			: m_Width(0), m_Height(0), m_Size(0)
		{
			m_Data = nullptr;
		}

	public:

		_SGOL_INLINE _SGOL_EXPLICIT vector2D(size_t width, size_t height)
			: m_Width(width), m_Height(height), m_Size(width * height)
		{
			m_Data = new Type[m_Size];
		}

		~vector2D()
		{
			delete[] m_Data;
			m_Data = nullptr;
			m_Size = 0;
		}

		_SGOL_INLINE Type& _SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL operator()(size_t x, size_t y) { return m_Data[x + y * m_Width]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator()(size_t x, size_t y) const { return m_Data[x + y * m_Width]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL Data() { return *m_Data; }

		_SGOL_INLINE size_t _SGOL_FASTCALL Size() { return m_Size; }

		_SGOL_INLINE size_t _SGOL_FASTCALL Width() { return m_Width; }
		_SGOL_INLINE size_t _SGOL_FASTCALL Height() { return m_Height; }
	
	private:

	private:
		size_t m_Width = 0;
		size_t m_Height = 0;
		size_t m_Size = 0;
		Type* m_Data = nullptr;
	};
}