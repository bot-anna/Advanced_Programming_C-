#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

template <size_t elementSize, typename IndexType> class PoolAllocator
{
private:

	struct Node {
		Node* next;
	};

	void* _pool = nullptr;
	const size_t _size;
	Node* _headNode;


public:
	PoolAllocator(size_t size) : _size(size)
	{
		if (_pool = static_cast<IndexType*>(std::malloc(_size * elementSize)))
		{
			_headNode = reinterpret_cast<Node*>(_pool);

			Node* node = _headNode;

			for (int i = 0; i < _size - 1; i++)
			{
				node->next = reinterpret_cast<Node*>(reinterpret_cast<char*>(node) + elementSize);
				node = node->next;
			}

			node->next = nullptr;
		}
		else
		{
			throw std::bad_alloc();
		}

	}

	template <typename T, typename... Args>
	T* create(Args&&... args)
	{
		

		if (sizeof(T) > elementSize)
		{
			return nullptr;
		}
		if (!_headNode)
		{
			throw std::bad_alloc();
		}


		void* address = reinterpret_cast<void*>(_headNode);

		_headNode = _headNode->next;
		return new(address) T(std::forward<Args>(args)...);
	}

	template <typename T>
	void destroy(T* ptr)
	{
		char* start = static_cast<char*>(_pool);
		char* end = start + (_size * elementSize);
		char* p = reinterpret_cast<char*>(ptr);

		if(p >= start && p < end)
		{
			Node* node = reinterpret_cast<Node*>(ptr);
			ptr->~T();
			node->next = _headNode;
			_headNode = node;
		}
	}

	int count_free() 
	{
		int count = 0;
		Node* node = _headNode;

		while (node)
		{
			count++;
			node = node->next;
		}
		return count;
	}

	std::string dump_pool() 
	{
		return "";
	}
};

#endif
