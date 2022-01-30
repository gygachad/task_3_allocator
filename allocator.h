#pragma once

#include "debug.h"

using namespace std;

template <class T>
class Allocator
{
public:
	bool* m_allocated = nullptr;
	T* m_mem_pool = nullptr;
	size_t m_default_items_count = 0x100;

	size_t m_mem_allocated = 0x0;

	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind { using other = Allocator<U>; };

	Allocator()
	{
		m_allocated = (bool*)malloc(sizeof(bool) * m_default_items_count);
		m_mem_pool = (T*)malloc(sizeof(T) * m_default_items_count);

		if (!m_allocated || !m_mem_pool)
			throw bad_alloc();

		memset(m_allocated, 0x0, sizeof(bool) * m_default_items_count);
		memset(m_mem_pool, 0x0, sizeof(T) * m_default_items_count);

		m_mem_allocated = sizeof(T) * m_default_items_count;

#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "Allocated pool " << m_mem_pool << endl;
#endif
	}

	~Allocator()
	{
		free(m_allocated);
		free(m_mem_pool);

#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "Free pool " << m_mem_pool << endl;
#endif
	}

	template <typename U>
	Allocator(const Allocator<U>& other)
	{
		m_allocated = (bool*)malloc(sizeof(bool) * m_default_items_count);
		m_mem_pool = (T*)malloc(sizeof(U) * m_default_items_count);

		if (!m_allocated || !m_mem_pool)
			throw bad_alloc();

		memcpy(m_allocated, other.m_allocated, sizeof(bool) * m_default_items_count);
		memcpy(m_mem_pool, other.m_mem_pool, sizeof(U) * m_default_items_count);

#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "Copy pool from " << other.m_mem_pool << " to " << m_mem_pool << endl;
#endif
	}

	T* allocate(size_t n)
	{
		/*
			auto p = malloc(n * sizeof(T));
			if (!p)
				throw bad_alloc();
				*/
		T* p = nullptr;

		//We need reallocate pool first
		if (n > m_default_items_count)
			return nullptr;

		for (size_t i = 0; i < m_default_items_count - n; i++)
		{
			bool success = true;

			for (size_t j = i; j < i + n; j++)
			{
				//This field already allocated. Try another one
				if (m_allocated[j])
				{
					success = false;
					break;
				}
			}

			if (success)
			{
				for (size_t j = i; j < i + n; j++)
				{
					m_allocated[j] = true;
				}

				p = m_mem_pool + i;

				break;
			}
		}

#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "allocate " << p << " from pool " << m_mem_pool << std::endl;
#endif
		return p;
	}

	void deallocate(T* p, size_t n)
	{
		UNUSED(n);
		//std::free(p);
		/*
		unsigned __int64 pos = p - m_mem_pool;

		for (size_t i = 0; i < n; i++)
		{
			m_allocated[pos] = false;
		}
		*/

#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "deallocate " << p << " from pool " << m_mem_pool << std::endl;
#endif
	}

	template <typename U, typename... Args>
	void construct(U* p, Args &&...args)
	{
#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "construct " << p << std::endl;
#endif

		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U* p)
	{
#ifdef DBG_PRINT
		PRINT_PRETTY();
		cout << "destroy " << p << std::endl;
#endif
		//p->~T();
	}
};