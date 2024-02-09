#ifndef SIMPLIFY_HPP
#define SIMPLIFY_HPP


#include <cstddef>
template<class T>
struct SimplifyType
{
	using type = T;
};

template<class T>
using SimplifyType_t = typename SimplifyType<T>::type;


template<class T>
struct SimplifyType<T*>
{
	using type = T;
};

template<class T>
struct SimplifyType<T&>
{
	using type = T;
};



template<class T>
struct SimplifyType<T[]>
{
	using type = T;
};


template<class T>
struct SimplifyType<const T>
{
	using type = T;
};


template<class T>
struct SimplifyType<const T*>
{
	using type = const T;
};

template<class T>
struct SimplifyType<const T**>
{
	using type = const typename SimplifyType<T>::type;
}; 

template<class T>
struct SimplifyType<const T&>
{
	using type = const T;
};

template<class T>
struct SimplifyType<T** const**>
{
	using type = T** const*;
};


template <class T>
struct BaseType
{
	using type = T;
};

template<class T>
using BaseType_t = typename BaseType<T>::type;

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

template<class T, std::size_t SZ>
struct BaseType<const T[SZ]>
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

#endif // !SIMPLIFY_HPP