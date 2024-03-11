#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

template <size_t ES, typename T> class PoolAllocator
{
private:

	struct Node {
		Node* next;
	};

	void* _data;
	const size_t _size;
	Node* _headNode;


public:
	PoolAllocator(size_t size) : _size(size) 
	{
		if (!(_pool = static_cast<T*>(std::malloc(_size * ES)))
		{
			throw std::bad_alloc();
		}

		size_t chunkCount = (_size / ES);
		for (auto index = 0; index < chunkCount; index++)
		{
			void* ptr = &_data[index * ES];
			Node* node = reinterpret_cast<Node*>(ptr);

			node->next = _headNode;
			_headNode = node;
		}

		 
	}

	template <typename T, typename... Args>
	void create(Args&&... args) 
	{
		static_assert(sizeof(T) <= elementSize, "Object too large for pool element");

		// Find a free element
		for (size_t i = 0; i < numElements; ++i) {
			if (freeList[i]) {
				freeList[i] = false; // Mark as used

				// Calculate the address for the new object
				void* addr = &data[i * elementSize];

				// Construct the object in the allocated space and return a pointer to it
				return new(addr) T(std::forward<Args>(args)...);
			}
		}

		Node* node = _headNode;
		if (node == nullptr)
		{
			return nullptr;
		}

		_headNode = _headNode->next;
		return reinterpret_cast<void*>(node);
	}

	void destroy(T* ptr) 
	{
		Node* node = reinterpret_cast<Node*>(ptr);
		node-> = _headNode;
		_headNode = node;
	}

	int count_free() {}

	std::string dump_pool() {}
};

#endif
