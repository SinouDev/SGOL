#pragma once

#include "sgol.h"

namespace sgol {

	template<typename _Ty, size_t width, size_t height>
	class array2D
	{
		using Type = _Ty;
	public:

		_SGOL_INLINE Type& _SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL operator()(size_t x, size_t y) { return m_Data[x + y * width]; }
		_SGOL_INLINE const Type& _SGOL_FASTCALL operator()(size_t x, size_t y) const { return m_Data[x + y * width]; }

		_SGOL_INLINE Type& _SGOL_FASTCALL Data() { return *m_Data; }

		_SGOL_CONSTEXPR _SGOL_INLINE size_t _SGOL_FASTCALL Size() { return width * height; }

		_SGOL_CONSTEXPR _SGOL_INLINE size_t _SGOL_FASTCALL Width() { return width; }
		_SGOL_CONSTEXPR _SGOL_INLINE size_t _SGOL_FASTCALL Height() { return height; }

	private:

	private:
		Type m_Data[width * height];
	};
}