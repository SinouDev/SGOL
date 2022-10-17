#pragma once

#include "SGOL.hpp"

namespace SGOL {

	template<typename Array>
	class ArrayIterator
	{
	public:

		using ValueType     = typename Array::ValueType;
		using ReferenceType = ValueType&;
		using PointerType   = ValueType*;

	public:

		ArrayIterator(PointerType ptr)
			: m_Ptr(ptr)
		{

		}

		__SGOL_CONSTEXPR bool operator!=(const ArrayIterator& it)
		{
			return m_Ptr != it.m_Ptr;
		}

		__SGOL_CONSTEXPR bool operator==(const ArrayIterator& it)
		{
			return m_Ptr == it.m_Ptr;
		}

		__SGOL_CONSTEXPR ArrayIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}

		__SGOL_CONSTEXPR ArrayIterator& operator++(int)
		{
			ArrayIterator tmp = *this;
			++(*this);
			return tmp;
		}

		__SGOL_CONSTEXPR ArrayIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}

		__SGOL_CONSTEXPR ArrayIterator& operator--(int)
		{
			ArrayIterator tmp = *this;
			--(*this);
			return tmp;
		}

		__SGOL_CONSTEXPR ReferenceType operator[](size_t index)
		{
			return *(*this + index);
		}

		__SGOL_CONSTEXPR ReferenceType operator*()
		{
			return *m_Ptr;
		}

		__SGOL_CONSTEXPR PointerType operator->()
		{
			return m_Ptr;
		}

	private:

		PointerType m_Ptr;

	};

	template<typename Type, size_t size>
	class Array
	{
	public:

		using ValueType = Type;
		using Iterator  = ArrayIterator<Array<Type, size>>;
		using ConstIterator = ArrayIterator<Array<Type, size>>;
		

	public:

		//template<typename... Args, typename EnableIf<size > 1, bool>::Type = true>
		//Array(Args&&... args)
		//{
		//	m_Data = std::forward<Args>(args)...;
		//}

		__SGOL_CONSTEXPR __SGOL_INLINE ValueType& __SGOL_FASTCALL operator[](size_t index) { return m_Data[index]; }
		__SGOL_CONSTEXPR __SGOL_INLINE const ValueType& __SGOL_FASTCALL operator[](size_t index) const { return m_Data[index]; }

		__SGOL_CONSTEXPR __SGOL_INLINE ValueType& __SGOL_FASTCALL Data() { return m_Data; }

		__SGOL_CONSTEXPR __SGOL_INLINE Iterator __SGOL_FASTCALL begin() { return Iterator(m_Data); }

		__SGOL_CONSTEXPR __SGOL_INLINE Iterator __SGOL_FASTCALL end() { return Iterator(m_Data + size); }

		__SGOL_CONSTEXPR __SGOL_INLINE size_t __SGOL_FASTCALL Size() { return size; }

		__SGOL_CONSTEXPR __SGOL_INLINE void __SGOL_FASTCALL Fill(ValueType fillValue)
		{
			for (size_t i = 0; i < size; i++)
				m_Data[i] = fillValue;
		}

	private:
		ValueType m_Data[size];
	};

}