#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

template <typename T> class SharedPtr {
private:
	T* _ptr;
	int* _count;
public:
	

	SharedPtr() noexcept : _ptr(nullptr), _count(nullptr){}
	//SharedPtr(nullptr) noexcept : _ptr(nullptr), _count(nullptr){}
	explicit SharedPtr(T* ptr) : _ptr(ptr) 
	{
		_count = new int(1);
		
	}
	SharedPtr(const SharedPtr& other) 
	{
		_ptr = other._ptr;
		_count = other._count;
		(*_count)++;
	} 
	SharedPtr(SharedPtr&& other) 
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
		else
		{
			delete _ptr;
			delete _count;
		}
	}

	//ASSIGNMENTS

	T& operator*()
	{

	}

	T& operator->()
	{

	}

	void reset()
	{

	}

	T* get()
	{
		return _ptr;
	} 

	int use_count()
	{
		return (_ptr ? *_count : 0);
	}

	bool Invariant() const
	{
		return true;
	}


};

#endif