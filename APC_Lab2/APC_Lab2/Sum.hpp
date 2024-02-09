#ifndef SUM_HPP
#define SUM_HPP
#include <type_traits>
#include <iterator>

template <class CONT>
auto Sum(const CONT& c)
{

	using type = decltype(*std::begin(c));
	using type_no_ref = std::remove_reference<type>::type;
	using type_no_const = std::remove_const<type_no_ref>::type;

	type_no_const sum = {};

	for (auto i : c)
	{
		sum += i;
	}

	return sum;
}


#endif