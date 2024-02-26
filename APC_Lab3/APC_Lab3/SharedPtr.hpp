#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP
#include <iostream>

template <typename T> class SharedPtr {
private:
	T* _ptr;
	int* _count;
	int* _wcount;
public:
	

	SharedPtr() noexcept : _ptr(nullptr), _count(nullptr){}
	SharedPtr(std::nullptr_t) noexcept : _ptr(nullptr), _count(nullptr){}
	explicit SharedPtr(T* ptr) : _ptr(ptr) 
	{
		_count = new int(1);
		
	}
	SharedPtr(const SharedPtr& other) 
	{
		_ptr = other._ptr;
		_count = other._count;

		if(_count) (*_count)++;
	} 
	SharedPtr(SharedPtr&& other) noexcept
	{
		_ptr = other._ptr;
		_count = other._count;

		other._ptr = nullptr;
		other._count = nullptr;
	}

	~SharedPtr ()
	{
		if (use_count() > 0)
		{
			(*_count)--;
		}
		if(use_count() == 0)
		{
			delete _ptr;
			delete _count;
		}
	}

	
	SharedPtr& operator=(const SharedPtr& other)
	{
		if (this == &other)
		{
			return *this;
		}
		if (use_count() == 1)
		{
			delete _count;
			delete _ptr;
		}
		else if(_count){
			--*_count;
		}
		_ptr = other._ptr;
		_count = other._count;

		if(_count) (*_count)++;

		return *this;
	}

	SharedPtr& operator=(SharedPtr&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		if (use_count() == 1)
		{
			delete _count;
			delete _ptr;
		}
		else if (_count){
			--*_count; //TODO nu kommer den hit om count är nullptr
		}
		_ptr = other._ptr;
		_count = other._count;

		other._ptr = nullptr;
		other._count = nullptr;
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	operator bool() const
	{
		return _ptr;
	}

	void reset()
	{
		if (use_count() == 1)
		{
			delete _count;
			delete _ptr;
			_count = nullptr;
			_ptr = nullptr;
		}
		else if(_count){
			--*_count;
			_ptr = nullptr;
			_count = nullptr;
		}
	}

	T* get()
	{
		return _ptr;
	} 

	int use_count()
	{
		return (_count ? *_count : 0);
	}

	bool Invariant() const
	{
		return true;
	}

	template<typename T>
	friend void swap(SharedPtr<T>& lhs, SharedPtr<T>& rhs) noexcept 
	{
		SharedPtr<T> temp(std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(temp);
	}


};

template<typename T>
bool operator==(SharedPtr<T>& lhs, SharedPtr<T>& rhs)
{
	return lhs.get() == rhs.get();
}

template<typename T>
bool operator==( SharedPtr<T>& lhs, std::nullptr_t)
{
	return lhs.get() == nullptr;
}

template<typename T>
bool operator==(std::nullptr_t, SharedPtr<T>& rhs)
{
	return nullptr == rhs.get();
}

template<typename T>
auto operator<=>(SharedPtr<T>& lhs, SharedPtr<T>& rhs)
{
	return lhs.get() <=> rhs.get();
}

template<typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args)
{
	return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif