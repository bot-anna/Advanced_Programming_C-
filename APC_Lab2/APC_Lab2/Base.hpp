#include <cstddef>
template <class T>
struct BaseType
{
	using type = T;
};

template<class T>
using Basetype_t = typename BaseType<T>::type;

template<class T>
struct BaseType<T*>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<T&>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<T[]>
{
	using type = typename BaseType<T>::type;
};

template<class T, std::size_t SZ>
struct BaseType<T[SZ]>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<const T>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<const T*>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<const T**>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<const T&>
{
	using type = typename BaseType<T>::type;
};

template<class T>
struct BaseType<T** const**>
{
	using type = typename BaseType<T>::type;
};