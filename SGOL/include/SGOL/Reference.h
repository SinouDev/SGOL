#pragma once

#include "Utils.h"

#include <type_traits>
#include <iostream>

class SS
{
public:

	SS(uint32_t a)
		: m_A(a)
	{
		std::cout << "SS created with " << a << std::endl;
	}

	SS()
		: m_A(50)
	{
		std::cout << "SS created" << std::endl;
	}

	SS(SS& ss)
		: m_A(ss.m_A)
	{
		std::cout << "SS copied" << std::endl;
	}

	SS(SS&& ss)
		: m_A(std::move(ss).m_A)
	{
		std::cout << "SS moved" << std::endl;
	}

	virtual ~SS()
	{
		std::cout << "SS destroyed" << std::endl;
	}

	virtual void Method() = 0;

private:
	uint32_t m_A;
};

class SS1 : public SS
{
public:
	virtual void Method() override
	{
		// Do something
	}
};

// simple Unique/Shared and Weak Pointers implementations
// Note:
// * Does not work with abstract classes
// * Not tested with premetive types pointers (should work tho)
namespace Utils::Reference {

#if 0
	template<typename T>
	class Unique
	{
	public:

		__UTILS_INLINE T* operator->()
		{
			return m_Ptr;
		}

		__UTILS_INLINE const T* operator->() const
		{
			return m_Ptr;
		}

		__UTILS_INLINE Unique(Unique&) = delete;
		__UTILS_INLINE Unique(Unique&&) = delete;

		__UTILS_INLINE Unique(T* ptr)
			: m_Ptr(ptr)
		{}

		__UTILS_INLINE ~Unique()
		{
			delete m_Ptr;
		}

	public:

		template<typename U>
		friend class Unique;

		template<typename U, typename... Args>
		friend __UTILS_INLINE Unique<U> MakeUnique(Args&&...);

	private:

		template<typename U, typename... Args>
		__UTILS_INLINE Unique(Args&&... args)
		{
			m_Ptr = new U(std::forward<Args>(args)...);
		}

		template<typename U>
		__UTILS_INLINE Unique<T>& operator=(Unique<U>&& u)
		{
			m_Ptr = u.m_Ptr;
		}

		//Unique()
		//	: m_Ptr(new T())
		//{
		//
		//}

	private:

		T* m_Ptr;
	};

#else

	template<typename T>
	class Unique
	{
	public:



		__UTILS_INLINE T* operator->()
		{
			return m_Ptr;
		}

		__UTILS_INLINE const T* operator->() const
		{
			return m_Ptr;
		}

		__UTILS_INLINE Unique(const Unique&) = delete;
		__UTILS_INLINE Unique& operator=(const Unique&) = delete;

		template<typename U, std::enable_if_t<std::conjunction_v<std::is_convertible<U*, T*>, std::is_same<T, U>>, int> = 0>
		__UTILS_INLINE Unique(Unique<U>&& right)
		{
			//static_assert(std::is_base_of<T, U>(), "");
			m_Ptr = right.m_Ptr;
			right.m_Ptr = nullptr;
		}

		__UTILS_INLINE Unique(T* ptr)
			: m_Ptr(ptr)
		{}

		__UTILS_INLINE ~Unique()
		{
			delete m_Ptr;
		}

		//template<typename U>
		//__UTILS_INLINE Unique<T>& operator=(Unique<U>&& u) noexcept
		//{
		//	m_Ptr = u.m_Ptr;
		//}

	public:

		template<typename>
		friend class Unique;

		template<typename U, typename... Args>
		friend __UTILS_INLINE Unique<U> MakeUnique(Args&&...);

	public:

		//template<typename... Args>
		//constexpr __UTILS_INLINE Unique(Args&&... args)
		//{
		//    m_Ptr = new T(std::forward<Args>(args)...);
		//}

		//template<typename U>
		//__UTILS_INLINE Unique<T>& operator=(Unique<U>&& u)
		//{
		//	m_Ptr = u.m_Ptr;
		//}

	private:

		T* m_Ptr;
	};

#endif

	template<typename T>
	class Weak;
	template<typename T>
	class Shared;

	template<typename T>
	class SharedObject
	{

		__UTILS_INLINE T* Get()
		{
			return m_Data;
		}
	
	private:

		__UTILS_INLINE SharedObject()
			: m_Count(0), m_Data(nullptr)
		{

		}

		template<typename U, typename... Args>
		__UTILS_INLINE SharedObject(Args&&... args)
			: m_Count(1), m_Data(new U(std::forward<Args>(args)...))
		{

		}

		__UTILS_INLINE ~SharedObject()
		{
			delete m_Data;
			//if (m_Count > 0) // this shouldn't be invoked if everything is alright
			//	__debugbreak();

		}

		template<typename U>
		friend class Shared;

		template<typename U>
		friend class Weak;

	private:
		size_t m_Count;
		T* m_Data;
	};

	template<typename T>
	class Shared
	{
	private:

	public:

		__UTILS_INLINE Shared(Shared& shared)
		{
			m_SharedObject = shared.m_SharedObject;
			//shared.m_SharedObject = nullptr;
			m_SharedObject->m_Count++;
		}

		__UTILS_INLINE Shared(const Shared& shared)
		{
			m_SharedObject = shared.m_SharedObject;
			//shared.m_SharedObject = nullptr;
			m_SharedObject->m_Count++;
		}

		__UTILS_INLINE Shared(Shared&& shared)
		{
			m_SharedObject = shared.m_SharedObject;
			shared.m_SharedObject = nullptr;
			m_SharedObject->m_Count++;
		}

		__UTILS_INLINE ~Shared()
		{
			if (!m_SharedObject)
				return;
			m_SharedObject->m_Count--;
			if (m_SharedObject->m_Count < 1)
				delete m_SharedObject;
		}

		__UTILS_INLINE T* operator->()
		{
			return m_SharedObject->m_Data;
		}

		__UTILS_INLINE const T* operator->() const
		{
			return m_SharedObject->m_Data;
		}

	public:

		template<typename U>
		friend class Weak;

		template<typename U>
		friend class Shared;

		template<typename U, typename... Args>
		friend static __UTILS_INLINE Shared<U> MakeShared(Args&&... args);

	private:

		template<typename U, typename... Args>
		__UTILS_INLINE Shared(Args&&... args)
		{
			m_SharedObject = new SharedObject<U>();
		}

	private:

		SharedObject<T>* m_SharedObject;
	};

	template<typename T>
	class Weak
	{
	public:
		__UTILS_INLINE Weak(Shared<T>& shared)
			: m_SharedObject(shared.m_SharedObject)
		{

		}

		__UTILS_INLINE T* operator->()
		{
			return m_SharedObject->m_Data;
		}

		__UTILS_INLINE const T* operator->() const
		{
			return m_SharedObject->m_Data;
		}

	public:
		SharedObject<T>* m_SharedObject;
	};

	template<typename T, typename... Args>
	__UTILS_NODISCARD static __UTILS_INLINE Shared<T> MakeShared(Args&&... args)
	{
		return Shared<T>(std::forward<Args>(args)...);
	}

	//template<typename U, typename... Args>
	//static __UTILS_INLINE Shared<U> MakeShared(Args&& ...args)
	//{
	//	return Shared<U>(std::forward<Args>(args)...);
	//}

	//template<typename T, typename... Args>
	//static __UTILS_INLINE Weak<T> MakeWeak(Args&&... args)
	//{
	//	return Shared<T>(std::forward<Args>(args)...);
	//}

	template<typename T, typename... Args>
	__UTILS_NODISCARD static __UTILS_INLINE Unique<T> MakeUnique(Args&&... args)
	{
		return Unique<T>(std::forward<Args>(args)...);
	}

}