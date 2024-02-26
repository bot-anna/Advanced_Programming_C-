#ifndef WEAKPTR_HPP
#define WEAKPTR_HPP
#include "SharedPtr.hpp"

template <typename T>
class WeakPtr
{
private:
	T* _ptr;
	int* _count;
	int* _wcount;

	WeakPtr() : _ptr(nullptr), _count(nullptr), _wcount(nullptr) {}
	explicit WeakPtr(WeakPtr& other)
	{
		_ptr = other._ptr;
		_count = other._count;
		_wcount = other._wcount;

		if (_wcount) (*_wcount)++;
	}

	WeakPtr(SharedPtr<T>& shared)
	{
		_ptr = shared._ptr;
		_count = shared._count;

		if (shared._wcount)
		{
			 (*shared._wcount)++;
		} 
		else
		{
			shared._wcount = new int(1);
		}
		_wcount = shared._wcount;
	}

	void reset()
	{
		_ptr = nullptr;
		_count = nullptr;
		if (_wcount)
		{
			(*_wcount)--;
		} 
	}

};

#endif // !WEAKPTR_HPP
