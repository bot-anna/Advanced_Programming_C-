#ifndef SFINAE_HPP
#define SFINAE_HPP

template <typename T, std::enable_if_t<std::is_nothrow_copy_constructible<T>::value, bool> = true>
bool NoThrowCopyConstructible(T)
{
	return true;
}

template <typename T, std::enable_if_t<!std::is_nothrow_copy_constructible<T>::value, bool> = true>
bool NoThrowCopyConstructible(T&)
{
	return false;
}

#endif // !SFINAE_HPP