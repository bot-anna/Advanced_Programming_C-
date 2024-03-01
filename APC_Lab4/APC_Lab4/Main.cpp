#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

std::mutex mtx;
std::vector<std::string> lines;
int _count;

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

bool read_file(const char* filename)
{
	std::string line;
	std::ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
		file.close();
		return true;
	}
	else return false;
}

int find_word(std::string line, const std::string searchFor)
{
	size_t index = 0;
	int count = 0;
	while ((index = line.find(searchFor, index)) != std::string::npos) {
		count++;
		index += searchFor.length();
	}
	return count;
}

void search_text(const std::string searchFor, int nbr_threads, int index)
{
	auto start = std::chrono::high_resolution_clock::now();
	size_t range = lines.size() / nbr_threads;
	size_t begin = range * index;
	size_t range_end = begin + range;
	int count = 0;

	for (int i = begin; i < range_end; i++)
	{
		count += find_word(lines[i], searchFor);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto execution_time_ms = duration.count();
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "Thread ID: " << std::this_thread::get_id << " found " << count << " occurences in " << execution_time_ms << " ms" << std::endl;;
}



void exercise_three(const char* filename, const std::string searchFor)
{
	
	if (read_file(filename))
	{
		const int nbr_threads = 100;
		std::thread threads[nbr_threads];
		
		std::cout << "Nbr of available hardware threads: " << std::thread::hardware_concurrency() << std::endl;
		std::cout << "Nbr of threads used for searching N = " << nbr_threads << std::endl;
		std::cout << "Lines per thread: " << lines.size() / nbr_threads << std::endl;
		std::cout << "Searching " << filename << " for '" << searchFor << "'" << std::endl;

		for (int i = 0; i < nbr_threads; i++)
		{
			threads[i] = std::thread(search_text,searchFor, nbr_threads, i);
		}
		for (int i = 0; i < nbr_threads; i++)
		{
			threads[i].join();
		}

		
	}
	else
	{
		throw std::invalid_argument("file could not be found");
	}
}

int find_word_two(std::string line, const std::string searchFor)
{
	size_t index = 0;
	int count = 0;
	while ((index = line.find(searchFor, index)) != std::string::npos) {
		count++;
		index += searchFor.length();
	}
	return count;
}

void search_text_two(const std::string searchFor, int nbr_threads, int index)
{
	auto start = std::chrono::high_resolution_clock::now();
	size_t range = lines.size() / nbr_threads;
	size_t begin = range * index;
	size_t range_end = begin + range;
	int count = 0;

	for (int i = begin; i < range_end; i++)
	{
		count += find_word_two(lines[i], searchFor);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto execution_time_ms = duration.count();
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "Thread ID: " << std::this_thread::get_id << " found " << count << " occurences in " << execution_time_ms << " ms" << std::endl;
	_count += count;
}

void exercise_three_p_two(const char* filename, const std::string searchFor)
{
	auto start = std::chrono::high_resolution_clock::now();

	if (read_file(filename))
	{
		const int nbr_threads = 73;
		std::thread threads[nbr_threads];

		std::cout << "Nbr of available hardware threads: " << std::thread::hardware_concurrency() << std::endl;
		std::cout << "Nbr of threads used for searching N = " << nbr_threads << std::endl;
		std::cout << "Lines per thread: " << lines.size() / nbr_threads << std::endl;
		std::cout << "Searching " << filename << " for '" << searchFor << "'" << std::endl;

		for (int i = 0; i < nbr_threads; i++)
		{
			threads[i] = std::thread(search_text_two, searchFor, nbr_threads, i);
		}
		for (int i = 0; i < nbr_threads; i++)
		{
			threads[i].join();
		}


	}
	else
	{
		throw std::invalid_argument("file could not be found");
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto execution_time_ms = duration.count();
	std::cout << "Total occurences found: " << _count << std::endl;
	std::cout << "Total execution time: " << execution_time_ms << " ms" << std::endl;
}

int main()
{
	//exercise_one();
	//exercise_two();
	//exercise_two_p_two();
	//exercise_three("bible.txt", "apple");
	exercise_three_p_two("bible.txt", "apple");

}
