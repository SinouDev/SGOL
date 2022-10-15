#pragma once

#include "SGOL.hpp"

// Simple Unique/Shared and Weak Pointers implementations
// Note:
// * Does not work with abstract classes
// * Not tested with premetive types pointers (should work tho)
namespace SGOL { namespace Reference {

	template<typename T>
	class Unique
	{
	private:

		using Ptr = T*;
	
		template<typename U, typename B>
		constexpr static bool s_IsConvertable = IsConvertable<typename Unique<U>::Ptr, typename Unique<B>::Ptr>();

	public:

		__SGOL_INLINE Ptr operator->()
		{
			return m_Ptr;
		}

		__SGOL_INLINE const Ptr operator->() const
		{
			return m_Ptr;
		}

		__SGOL_INLINE Unique(const Unique&) = delete;
		__SGOL_INLINE Unique& operator=(const Unique&) = delete;

		//template <class U, std::enable_if_t<std::conjunction_v<std::negation<std::is_array<U>>, std::is_convertible<typename Unique<U>::Ptr, Ptr>>, int> = 0>
		
		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE Unique(Unique<U>&& right) noexcept
		{
			static_assert(std::is_base_of<T, U>(), "");
			m_Ptr = right.m_Ptr;
			right.m_Ptr = nullptr;
		}

		__SGOL_INLINE Unique(Ptr ptr)
			: m_Ptr(ptr)
		{}

		__SGOL_INLINE ~Unique()
		{
			delete m_Ptr;
		}

	public:

		template<typename>
		friend class Unique;

		template<typename U, typename... Args>
		friend __SGOL_INLINE Unique<U> MakeUnique(Args&&...);

	private:

		Ptr m_Ptr;
	};

	template<typename T>
	class Weak;
	template<typename T>
	class Shared;

	template<typename T>
	class SharedObject
	{
	private:

		using Ptr = T*;

		template<typename U, typename B>
		constexpr static bool s_IsConvertable = IsConvertable<typename SharedObject<U>::Ptr, typename SharedObject<B>::Ptr>();

	public:

		__SGOL_INLINE T* Get()
		{
			return m_Ptr;
		}

	private:

		__SGOL_INLINE SharedObject()
			: m_Count(0), m_Ptr(nullptr)
		{

		}

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE SharedObject(const SharedObject<U>& sharedObject)
			: m_Count(sharedObject.m_Count), m_Ptr(sharedObject.m_Ptr)
		{

		}

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE SharedObject(SharedObject<U>& sharedObject)
			: m_Count(sharedObject.m_Count), m_Ptr(sharedObject.m_Ptr)
		{

		}

		//template<typename U, typename... Args>
		//__SGOL_INLINE SharedObject(Args&&... args)
		//	: m_Count(1), m_Ptr(new U(std::forward<Args>(args)...))
		//{
		//
		//}

		__SGOL_INLINE SharedObject(Ptr ptr)
			: m_Count(1), m_Ptr(ptr)
		{

		}

		__SGOL_INLINE ~SharedObject()
		{
			delete m_Ptr;
			//if (m_Count > 0) // this shouldn't be invoked if everything is alright
			//	__debugbreak();
		}

		template<typename>
		friend class Shared;

		template<typename>
		friend class Weak;

		template<typename>
		friend class SharedObject;

	private:
		size_t m_Count;
		Ptr m_Ptr;
	};

	template<typename T>
	class Shared
	{
	private:

		using SharedObjectInstance = SharedObject<T>;
		using SharedObjectInstancePtr = SharedObjectInstance*;
		using SharedPtr = typename SharedObjectInstance::Ptr;

		template<typename U, typename B>
		constexpr static bool s_IsConvertable = IsConvertable<typename Shared<U>::SharedPtr, typename Shared<B>::SharedPtr>();

	public:

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE Shared(Shared<U>& shared)
			: m_SharedObject((SharedObjectInstancePtr)shared.m_SharedObject)
		{
			//shared.m_SharedObject = nullptr;
			m_SharedObject->m_Count++;
		}

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE Shared(const Shared<U>& shared)
			: m_SharedObject((SharedObjectInstancePtr)shared.m_SharedObject)
		{
			//shared.m_SharedObject = nullptr;
			m_SharedObject->m_Count++;
		}

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE Shared(Shared<U>&& shared) noexcept
			: m_SharedObject((SharedObjectInstancePtr)shared.m_SharedObject)
		{
			shared.m_SharedObject = nullptr;
			//m_SharedObject->m_Count++;
		}

		__SGOL_INLINE ~Shared()
		{
			if (!m_SharedObject)
				return;
			m_SharedObject->m_Count--;
			if (m_SharedObject->m_Count < 1)
				delete m_SharedObject;
		}

		__SGOL_INLINE T* operator->()
		{
			return m_SharedObject->m_Ptr;
		}

		__SGOL_INLINE const T* operator->() const
		{
			return m_SharedObject->m_Ptr;
		}


		template<typename U>
		__SGOL_INLINE Shared(U* right)
		{
			m_SharedObject = new SharedObject<U>(right);
		}

	private:

		template<typename>
		friend class Weak;

		template<typename>
		friend class Shared;

		template<typename U, typename... Args>
		friend __SGOL_INLINE Shared<U> MakeShared(Args&&... args);

	private:

		SharedObjectInstancePtr m_SharedObject;
	};

	template<typename T>
	class Weak
	{
	private:

		using SharedObjectInstance = SharedObject<T>;
		using SharedObjectInstancePtr = SharedObjectInstance*;
		using SharedPtr = typename SharedObjectInstance::Ptr;

		template<typename U, typename B>
		constexpr static bool s_IsConvertable = IsConvertable<typename Shared<U>::SharedPtr, typename Shared<B>::SharedPtr>();

	public:

		template<typename U, typename EnableIf<s_IsConvertable<U, T>, bool>::Type = true>
		__SGOL_INLINE Weak(Shared<U>& shared)
			: m_SharedObject((SharedObjectInstancePtr)shared.m_SharedObject)
		{
			m_SharedObject->m_Ptr = shared.m_SharedObject->m_Ptr;
			m_SharedObject->m_Count = shared.m_SharedObject->m_Count;
		}

		__SGOL_INLINE SharedPtr operator->()
		{
			return m_SharedObject->m_Ptr;
		}

		__SGOL_INLINE const T* operator->() const
		{
			return m_SharedObject->m_Ptr;
		}

	public:
		SharedObjectInstancePtr m_SharedObject;
	};

	template<typename T, typename... Args>
	__SGOL_NODISCARD static __SGOL_INLINE Shared<T> MakeShared(Args&&... args)
	{
		return Shared<T>(new T(std::forward<Args>(args)...));
	}

	template<typename T, typename... Args>
	__SGOL_NODISCARD static __SGOL_INLINE Unique<T> MakeUnique(Args&&... args)
	{
		return Unique<T>(new T(std::forward<Args>(args)...));
	}

} }