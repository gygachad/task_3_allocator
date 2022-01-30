#pragma once

using namespace std;

template <class T>
struct Allocator
{
	//public:
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind { using other = Allocator<U>; };

	Allocator() = default;
	~Allocator() = default;

	template <typename U>
	Allocator(const Allocator<U>&) {}

	T* allocate(size_t n)
	{
		PRINT_PRETTY();
		cout << "allocate" << std::endl;

		auto p = malloc(n * sizeof(T));
		if (!p)
			throw bad_alloc();
		return reinterpret_cast<T*>(p);
	}

	void deallocate(T* p, size_t n)
	{
		UNUSED(n);
		PRINT_PRETTY();
		cout << "deallocate" << std::endl;

		std::free(p);
	}

	template <typename U, typename... Args>
	void construct(U* p, Args &&...args)
	{
		PRINT_PRETTY();
		cout << "construct" << std::endl;

		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U* p)
	{
		UNUSED(p);
		PRINT_PRETTY();
		cout << "destroy" << std::endl;

		//p->~T();
	}
};