#pragma once

#include "SGOL.hpp"
#include "cuda_runtime.h"

namespace SGOL {
	
	//
	// Simple 2D array class
	//
	// DataType: It is the underline data type
	// Note: Currently it's used for premetive types only
	template<typename DataType>
	class Array2D
	{
	public:

		using Type = DataType;

	public:

		__SGOL_INLINE Array2D(size_t width, size_t height)
			: m_Width(width), m_Height(height), m_Size(width * height)
		{
			m_Data = new DataType[m_Size];
			_ASSERT(m_Data);
		}

		__SGOL_INLINE Array2D()
		{}

		virtual __device__ __host__ ~Array2D()
		{
			if (m_UserHandle)
				return;
			if constexpr (std::is_class_v<DataType>)
				delete[] m_Data;
			else delete m_Data;
		}

		DataType* begin()
		{
			return &m_Data[0];
		}

		DataType* end()
		{
			return &m_Data[m_Size];
		}

		__SGOL_INLINE operator const DataType* ()
		{
			return m_Data;
		}

		__SGOL_INLINE operator DataType* ()
		{
			return m_Data;
		}

		__SGOL_INLINE void __SGOL_FASTCALL SaveAndResize(size_t width, size_t height)
		{
			DataType* data = new DataType[width * height];

			for (size_t y = 0; y < m_Height; y++)
			{
				for (size_t x = 0; x < m_Width; x++)
				{
					size_t i = x + y * m_Width;
					data[i] = m_Data[i];
				}
			}

			delete[] m_Data;
			m_Data = data;
			m_Height = height;
			m_Width = width;
			m_Size = width * height;
		}

		__host__ __device__ __SGOL_INLINE size_t __SGOL_FASTCALL Index(size_t x, size_t y)
		{
			return x + y * m_Width;
		}

		// Resize will delete old data without saving it
		virtual __SGOL_INLINE void __SGOL_FASTCALL Resize(size_t width, size_t height)
		{
			delete[] m_Data;

			//m_Height = height;
			//m_Width = width;
			//m_Size = width * height;
			//m_Data = new DataType[m_Size];

			m_Data = new DataType[m_Size = (m_Width = width) * (m_Height = height)];
		}

		__SGOL_INLINE void __SGOL_FASTCALL Fill(DataType fillValue)
		{
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i] = fillValue;
		}
		
		template<typename T>
		__host__ __device__ __SGOL_INLINE T __SGOL_FASTCALL Width() const
		{
			return static_cast<T>(m_Width);
		}

		__device__ __host__ __SGOL_INLINE size_t __SGOL_FASTCALL Width() const
		{
			return m_Width;
		}
		
		template<typename T>
		__host__ __device__ __SGOL_INLINE T __SGOL_FASTCALL Height() const
		{
			return static_cast<T>(m_Height);
		}

		__host__ __device__ __SGOL_INLINE size_t __SGOL_FASTCALL Height() const
		{
			return m_Height;
		}
		
		template<typename T>
		__SGOL_INLINE T __SGOL_FASTCALL Size() const
		{
			return static_cast<T>(m_Size);
		}

		__host__ __device__ __SGOL_INLINE size_t __SGOL_FASTCALL Size() const
		{
			return m_Size;
		}

		template<typename T>
		__SGOL_INLINE T* __SGOL_FASTCALL Data()
		{
			return static_cast<T*>(m_Data);
		}

		__SGOL_INLINE DataType* __SGOL_FASTCALL Data()
		{
			return m_Data;
		}

		const __SGOL_INLINE DataType* __SGOL_FASTCALL Data() const
		{
			return m_Data;
		}

		__SGOL_INLINE Array2D<DataType>& __SGOL_FASTCALL Get()
		{
			return *this;
		}

		const __SGOL_INLINE Array2D<DataType>& __SGOL_FASTCALL Get() const
		{
			return *this;
		}

		__device__ __host__ __SGOL_INLINE DataType& __SGOL_FASTCALL operator()(size_t x, size_t y)
		{
			return m_Data[x + y * m_Width];
		}

		__device__ __host__ __SGOL_INLINE const DataType& __SGOL_FASTCALL operator()(size_t x, size_t y) const
		{
			return m_Data[x + y * m_Width];
		}

		__device__ __host__ __SGOL_INLINE DataType& __SGOL_FASTCALL operator[](size_t i)
		{
			return m_Data[i];
		}

		//template<typename T>
		//__SGOL_INLINE T& __SGOL_FASTCALL operator[](size_t i)
		//{
		//	return reinterpret_cast<T*>(m_Data)[i];
		//}

		const __SGOL_INLINE DataType& __SGOL_FASTCALL operator[](size_t i) const
		{
			return m_Data[i];
		}

	protected:

		size_t m_Width = 0;
		size_t m_Height = 0;
		size_t m_Size = 0;
		DataType* m_Data = nullptr;
		bool m_UserHandle = false;
	};
}