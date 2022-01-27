#pragma once

using namespace std;

#ifdef _MSC_VER 
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define PRINT_PRETTY() std::cout << __PRETTY_FUNCTION__ << endl

template <class T>
class Allocator 
{
public:
    using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U>
	struct rebind {	using other = Allocator<U>;	};

	Allocator() = default;
	~Allocator() = default;

	template <typename U>
	Allocator(const Allocator<U>&) {};

	T* allocate(size_t n);
	void deallocate(T* p, size_t n);

	template <typename U, typename... Args>
	void construct(U* p, Args &&...args);

	template <typename U>
	void destroy(U* p);
};