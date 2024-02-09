#ifndef REMALLCONST_HPP
#define REMALLCONST_HPP

template<class T>
struct RAC
{
	using type = T;
};

template<class T>
struct RAC<const T>
{
	using type = RAC<T>::type;
};

template<class T>
struct RAC<T*> {
	using type = typename RAC<T>::type*;
};


#endif