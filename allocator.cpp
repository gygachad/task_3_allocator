#include "allocator.h"

template <typename T>
T* Allocator<T>::allocate(size_t n)
{
	PRINT_PRETTY();

	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T*>(p);
}

template <typename T>
void Allocator<T>::deallocate(T* p, size_t n)
{
	PRINT_PRETTY();

	std::free(p);
}

template <typename T>
template <typename U, typename... Args>
void Allocator<T>::construct(U* p, Args &&...args)
{
	PRINT_PRETTY();

	cout << "construct" << std::endl;
	new (p) U(std::forward<Args>(args)...);
};

template <typename T>
template <typename U>
void Allocator<T>::destroy(U* p)
{
	PRINT_PRETTY();

	cout << "destroy" << std::endl;
	p->~T();
}
