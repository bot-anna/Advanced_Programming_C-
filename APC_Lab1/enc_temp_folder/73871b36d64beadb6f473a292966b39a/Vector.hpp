#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>
#include <cassert>
#include <iterator>
#include <ostream>

template <typename T> class Vector
{

private:
	size_t _size;
	size_t _cap;
	T* _ptr;

	template<typename CT, int DIR>
	class VectorIterDir
	{
	private:
		CT* _ptr; //todo public?
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = CT;
		using difference_type = std::ptrdiff_t;
		using pointer = CT*;
		using reference = CT&;

		VectorIterDir(CT* p) : _ptr(p) {}
		VectorIterDir() : _ptr(nullptr) {}
		VectorIterDir(const VectorIterDir& other)
		{
			_ptr = other._ptr;
		}
		VectorIterDir& operator=(const VectorIterDir& other)
		{
			_ptr = other._ptr;
			return *this;
		}
		CT& operator*() const
		{
			return *_ptr;
		}
		CT* operator->() const
		{
			return _ptr;
		}
		CT& operator[](size_t i) const
		{
			return _ptr[i];
		}
		VectorIterDir& operator++()
		{
			_ptr += DIR;
			return *this;
		}
		VectorIterDir& operator--()
		{
			_ptr -= DIR;
			return *this;
		}
		VectorIterDir operator++(int)
		{
			auto temp = *this;
			_ptr += DIR;
			return temp;
		}
		VectorIterDir operator--(int)
		{
			auto temp = *this;
			_ptr -= DIR;
			return temp;
		}
		VectorIterDir& operator+=(difference_type i)
		{
			_ptr += (i * DIR);
			return *this;
		}

		VectorIterDir operator+(difference_type i) const
		{
			return VectorIterDir(*this) += (i * DIR);
		}

		VectorIterDir operator-(difference_type i) const
		{
			return VectorIterDir(_ptr - (i * DIR));
		}

		difference_type operator-(const VectorIterDir& other) const
		{
			return _ptr - (other._ptr * DIR);
		}

		friend bool operator==(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr == rhs._ptr;
		}

		friend bool operator!=(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr != rhs._ptr;
		}

		friend bool operator<(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr < rhs._ptr;
		}

		friend bool operator>(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr > rhs._ptr;
		}

		friend bool operator<=(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr <= rhs._ptr;
		}

		friend bool operator>=(const VectorIterDir& lhs, const VectorIterDir& rhs)
		{
			return lhs._ptr >= rhs._ptr;
		}
	};
	

#define CHECK assert(Invariant());
public:

	using iterator = VectorIterDir<T, +1>;
	using const_iterator = VectorIterDir<const T, +1>;
	using reverse_iterator = VectorIterDir < T, -1>;
	using reverse_const_iterator = VectorIterDir<const T, -1>;

	~Vector() noexcept
	{
		delete[] _ptr;
	}

	Vector() noexcept
	{
		_size = 0;
		_cap = 0;
		_ptr = nullptr;
		CHECK
	}

	Vector(const char* other)
	{
		_size = strlen(other);
		_cap = _size;
		_ptr = new char[_cap];
		size_t i;
		for (i = 0; i < _cap; i++)
		{
			_ptr[i] = other[i];
		}
		CHECK
	}
	Vector(const Vector& other)
	{
		_size = other._size;
		_cap = other._cap;
		_ptr = new T[_cap];

		for (size_t i = 0; i < _size; i++)
		{
			_ptr[i] = other._ptr[i];
		}
		CHECK
	}
	Vector(Vector&& other) noexcept
	{
		_size = other._size;
		_cap = other._cap;
		_ptr = other._ptr;

		other._size = 0;
		other._cap = 0;
		other._ptr = nullptr;
		CHECK
	}

	Vector& operator=(const Vector& other)
	{
		_size = other._size;
		_cap = other._cap;
		_ptr = new T[other._cap];

		for (size_t i = 0; i < _size; i++)
		{
			_ptr[i] = other._ptr[i];
		}
		CHECK
		return *this;
	}

	Vector& operator=(Vector&& other)
	{
		_size = other._size;
		_cap = other._cap;
		_ptr = other._ptr;

		other._size = 0;
		other._cap = 0;
		other._ptr = nullptr;

		CHECK
		return *this;
	}

	T& operator[](size_t i)
	{
		return _ptr[i];
	}

	const T& operator[](size_t i) const
	{
		return _ptr[i];
	}

	T& at(size_t i)
	{
		if ((i < 0) || (i >= _size))
		{
			throw std::out_of_range(" index out of range");
		}

		return _ptr[i];
	}

	const T& at(size_t i) const
	{
		if ((i < 0) || (i >= _size))
		{
			throw std::out_of_range(" index out of range");
		}

		return _ptr[i];
	}

	T* data() noexcept
	{
		return _ptr;
	}
	const T* data() const noexcept
	{
		return _ptr;
	}
	size_t size() const noexcept
	{
		return _size;
	}

	size_t capacity() const noexcept
	{
		return _cap;
	}
	void reserve(size_t n)
	{
		if (n < _size)
		{
			return;
		}

		T* temp = new T[n];
		for (size_t i = 0; i < _size; i++)
		{
			temp[i] = _ptr[i];
		}

		delete[] _ptr;
		_ptr = temp;
		_cap = n;
		CHECK
	}
	void shrink_to_fit()
	{
		if (_size < _cap)
		{
			T* temp = new T[_size];
			for (size_t i = 0; i < _size; i++)
			{
				temp[i] = _ptr[i];
			}

			delete[] _ptr;
			_ptr = temp;
			_cap = _size;
		}
		CHECK

	}

	void resize(size_t n)
	{
		if (n > _cap)
		{
			reserve(n);
		}
		if (n > _size)
		{
			for (size_t i = _size; i < n; i++)
			{
				_ptr[i] = T();
			}
		}

		_size = n;
		CHECK
	}
	void push_back(const T& c)
	{
		if (_ptr == nullptr)
		{
			reserve(1);
		}
		if (_size >= _cap)
		{
			reserve(_size * 2);
		}

		_ptr[_size] = c;
		_size++;
		CHECK
	}
	void pop_back()
	{
		if (_size == 0)
		{
			return;
		}

		//T[_size] = T();
		_size--;
		CHECK
	}

	friend bool operator==(const Vector& lhs, const Vector& rhs)
	{
		if (lhs._size != rhs._size)
		{
			return false;
		}
		
		auto l_iter = lhs.begin();
		auto r_iter = rhs.begin();
		
		while (l_iter != lhs.end())
		{
			if (*l_iter++ != *r_iter++)
			{
				return false;
			}
		}
		return true;

		
	}
	friend bool operator<(const Vector& lhs, const Vector& rhs)
	{
		auto l_iter = lhs.begin();
		auto r_iter = rhs.begin();

		while (l_iter != lhs.end())
		{
			if (*(l_iter++) > *(r_iter++))
			{
				return false;
			}
		}
		return true;
	}
	friend bool operator>(const Vector& lhs, const Vector& rhs)
	{
		return !(lhs < rhs);
	}
	friend bool operator!=(const Vector& lhs, const Vector& rhs)
	{
		return !(lhs == rhs);
	}
	friend bool operator<=(const Vector& lhs, const Vector& rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	}
	friend bool operator>=(const Vector& lhs, const Vector& rhs)
	{
		return (lhs > rhs) || (lhs == rhs);
	}

	iterator begin() noexcept
	{
		return iterator(_ptr);
	}
	iterator end() noexcept
	{
		return iterator(_ptr + _size);
	}
	const_iterator begin() const noexcept
	{
		return const_iterator(_ptr);
	}
	const_iterator end() const noexcept
	{
		return const_iterator(_ptr + _size);
	}
	const_iterator cbegin() const noexcept
	{
		return const_iterator(_ptr);
	}
	const_iterator cend() const noexcept
	{
		return const_iterator(_ptr + _size);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(_ptr + _size - 1); //hmm
	}
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(_ptr);
	}
	reverse_const_iterator rbegin() const noexcept
	{
		return reverse_const_iterator(_ptr + _size - 1);
	}
	reverse_const_iterator rend() const noexcept
	{
		return reverse_const_iterator(_ptr);
	}
	reverse_const_iterator crbegin() const noexcept
	{
		return reverse_const_iterator(_ptr + _size - 1);
	}
	reverse_const_iterator crend() const noexcept
	{
		return reverse_const_iterator(_ptr);
	}

	

	friend std::ostream& operator<<(std::ostream& cout, const Vector& other) {
		for (size_t i = 0; i < other.size(); ++i)
			cout << other[i];
		return cout;
	}

	bool Invariant() const
	{
		return true;
	}
};
	template<class T>
	void swap(Vector<T>& lhs, Vector<T>& rhs)
	{
		Vector<T> temp(std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(temp);
	}

	
#endif // !VECTOR_HPP

	
