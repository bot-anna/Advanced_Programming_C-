#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void increment_elements(std::vector<int>& v, int index, int nbr_threads)
{
	size_t range = v.size() / nbr_threads;
	size_t begin = range * index;
	size_t end = begin + range;

	for (size_t i = begin; i < end; i++)
	{
		v[i] += index;
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void print_vector(const char* time, const std::vector<int> v)
{
	std::cout << time;

	for (auto i : v)
	{
		std::cout << i;
	}
	std::cout << std::endl;
}

void thread_greetings(int id)
{
	mtx.lock();
	std::cout << "Hello from thread " << id << "!" << std::endl;
	mtx.unlock();
}

void thread_greetings_lock(int id)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "Hello from thread " << id << "!" << std::endl;
}

void exercise_one()
{
	std::vector<int> v(20, 0);
	print_vector("Before: ", v);

	const int nbr_threads = 5;
	std::thread threads[nbr_threads];


	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i] = std::thread(increment_elements, std::ref(v), i, nbr_threads);
	}

	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i].join();
	}

	print_vector("After: ", v);
}

void exercise_two()
{
	const int nbr_threads = 10;
	std::thread threads[nbr_threads];


	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i] = std::thread(thread_greetings, i);
	}
	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i].join();
	}
}

void exercise_two_p_two()
{
	const int nbr_threads = 10;
	std::thread threads[nbr_threads];


	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i] = std::thread(thread_greetings_lock, i);
	}
	for (int i = 0; i < nbr_threads; i++)
	{
		threads[i].join();
	}
}

int main()
{
	//exercise_one();
	//exercise_two();
	exercise_two_p_two();

}
