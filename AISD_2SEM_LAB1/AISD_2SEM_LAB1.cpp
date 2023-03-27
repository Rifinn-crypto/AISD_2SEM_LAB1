#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <chrono>
#include <ctime> 

template <typename T>
struct node
{
	T data;
	node* left;
	node* right;
	node(T key)
	{
		left = nullptr;
		right = nullptr;
		data = key;
	}
};

template <typename T>
class BinaryTree
{
private:
	node<T>* root;
	int size;

	void print_tree(node<T>* current, int level)
	{
		std::string lvl(level, ' ');
		if (!current)
		{
			std::cout << lvl << "null" << std::endl;
			return;
		}
		std::cout << lvl << current->data << std::endl;
		print_tree(current->left, level + 1);
		print_tree(current->right, level + 1);
	}


	node<T>* remove(node<T>* current, T key)
	{
		if (!current)
		{
			return nullptr;
		}
		if (current->data < key)
			current->right = remove(current->right, key);
		if (current->data > key)
			current->left = remove(current->left, key);
		if (current->data == key)
		{
			if (!current->left && !current->right)
			{
				delete current;
				current = nullptr;
				return current;
			}
			if (!current->left && current->right)
			{
				node<T>* tmp = current->right;
				delete current;
				return tmp;
			}
			if (current->left && !current->right)
			{
				node<T>* tmp = current->left;
				delete current;
				return tmp;
			}
			if (current->left && current->right)
			{
				node<T>* new_current = current->right;
				while (new_current->left)
				{
					new_current = new_current->left;
				}
				current->data = new_current->data;
				current->right = remove(current->right, new_current->data);
				return current;
			}
		}
	}
public:
	BinaryTree(T number)
	{
		size = 1;
		root = new node<T>(number);
	}

	BinaryTree()
	{
		size = 0;
		root = nullptr;
	}

	void insert(node<T>* current, T key)
	{
		if (!current)
		{
			current = new node<T>(key);
			return;
		}
		if (current->data < key)
			insert(current->right, key);
		if (current->data > key)
			insert(current->left, key);
	}

	void remove_norm(T key)
	{
		if (!root)
		{
			return;
		}
		if (!contains(key))
		{
			return;
		}
		root = remove(root, key);
	}

	bool contains(T key)
	{
		node<T>* tmp = root;
		while (tmp && tmp->data != key)
		{
			if (tmp->data < key)
			{
				tmp = tmp->right;
			}
			else
			{
				tmp = tmp->left;
			}
		}
		return tmp != nullptr;
	}

	void printr()
	{
		print_tree(root, 0);
	}


	void insert(T key)
	{
		if (!root)
		{
			size++;
			root = new node<T>(key);
			return;
		}// 1 2 3 4 1 1 57 28
		if (contains(key))
			return;
		node<T>* current = root;
		while (current)
		{
			if (current->data > key)
			{
				if (current->left == nullptr)
				{
					current->left = new node<T>(key);
					size++;
					return;
				}
				else
					current = current->left;
			}

			if (current->data < key)
			{
				if (current->right == nullptr)
				{
					current->right = new node<T>(key);
					size++;
					return;
				}
				else
					current = current->right;
			}
		}
	}
};
/*
Напишите функции, возвращающие объединение и симметрическую разность 2-х множеств целых чисел
A = { 1, 2, 3 , 4 }
B = { 4, 5, 6 }
C = { 1, 2, 3, 4, 5, 6 } - Объединение хотя бы 1 из множеств
D = Симм разность = 1, 2, 3, 5, 6 - либо там, либо там
*/

template<typename T>
bool Contains(std::vector<T>& vec, T element)
{
	if (std::find(vec.begin(), vec.end(), element) != vec.end())
		return true;
	return false;
}


std::pair <std::vector<int>, std::vector<int>> operations(std::vector<int>& first, std::vector<int>& second)
{
	std::pair<std::vector<int>, std::vector<int>> pr;
	std::vector<int> unification;
	std::vector<int> difference;

	for (int i = 0; i < first.size(); i++)
	{
		unification.push_back(first[i]);
	}
	for (int i = 0; i < second.size(); i++)
	{
		if (!Contains(first, second[i]))
		{
			unification.push_back(second[i]);
		}
	}

	for (int i = 0; i < second.size(); i++)
	{
		if (!Contains(first, second[i]))
		{
			difference.push_back(second[i]);
		}
	}

	for (int i = 0; i < first.size(); i++)
	{
		if (!Contains(second, first[i]))
		{
			difference.push_back(first[i]);
		}
	}

	pr.first = unification;
	pr.second = difference;
	return pr;
}

void task_second()
{
	std::vector<int> first;
	for (int i = 1; i < 5; i++)
		first.push_back(i);
	std::vector<int> second;
	for (int i = 4; i < 7; i++)
		second.push_back(i);
	auto res = operations(first, second);
	auto res_first = res.first;
	auto res_second = res.second;

	std::cout << "unification ";
	for (int i = 0; i < res_first.size(); i++)
	{
		std::cout << res_first[i] << " ";
	}
	std::cout << "difference ";
	for (int i = 0; i < res_second.size(); i++)
	{
		std::cout << res_second[i] << " ";
	}
}

//void tree_test()
//{
//
//}

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

template<typename T>
std::pair<std::chrono::duration<double>, std::vector<T>> time_generate_vector_collection(int step, int count)
{
	int interval = count / step;
	std::pair<std::chrono::duration<double>, std::vector<T>> pr;
	std::chrono::duration<double> time{ 0 };
	std::vector<T> vector;
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			vector.push_back(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	pr.first = time;
	pr.second = vector;
	return pr;
}

template <typename T>
std::chrono::duration<double> time_generate_tree_collection(BinaryTree<T>& tree, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			tree.insert(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}

template<typename T>
std::chrono::duration<double> time_find_vector_collection(std::vector<T>& vector, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			Contains(vector, lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}


template <typename T>
std::chrono::duration<double> time_find_tree_collection(BinaryTree<T>& tree, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			tree.contains(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}

template<typename T>
std::chrono::duration<double> time_add_vector_collection(std::vector<T> vector, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			vector.push_back(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}
template<typename T>
std::chrono::duration<double> time_add_tree_collection(BinaryTree<T>& tree, int step, int count) //***
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			tree.insert(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}

template<typename T>
std::chrono::duration<double> time_remove_vector_collection(std::vector<T> vector, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			remove(vector.begin(), vector.end(), lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}
//remove_norm
template<typename T>
std::chrono::duration<double> time_remove_tree_collection(BinaryTree<T>& tree, int step, int count)
{
	int interval = count / step;
	std::chrono::duration<double> time{ 0 };
	for (size_t i = 0; i < interval; i++)
	{
		auto time_start = std::chrono::system_clock::now();
		for (size_t i = 0; i < step; i++)
		{
			tree.remove_norm(lcg());
		}
		auto time_end = std::chrono::system_clock::now();
		time += time_end - time_start;
	}
	time /= step;
	return time;
}

void timeTestVector()
{
	auto pair1_000 = time_generate_vector_collection<size_t>(100, 1000);
	auto vect1_000 = pair1_000.second;
	auto pair10_000 = time_generate_vector_collection<size_t>(100, 10000);
	auto vect10_000 = pair10_000.second;
	auto pair100_000 = time_generate_vector_collection<size_t>(100, 100000);
	auto vect100_000 = pair100_000.second;
	std::cout << "Average time generate 1000 elements of Vector ::::::" << pair1_000.first.count() << std::endl;
	std::cout << "Average time generate 10000 elements of Vector ::::::" << pair10_000.first.count() << std::endl;
	std::cout << "Average time generate 100000 elements of Vector ::::::" << pair100_000.first.count() << std::endl;

	auto findTime1_000 = time_find_vector_collection<size_t>(vect1_000, 1000, 1000);
	std::cout << "Average time find in container of 1000 elements of Vector ::::::" << findTime1_000.count() << std::endl;


	auto addTime1_000 = time_add_vector_collection<size_t>(vect1_000, 1000, 1000);
	std::cout << "Average time ADD in container of 1000 elements of Vector ::::::" << addTime1_000.count() << std::endl;

	auto removeTime1_000 = time_remove_vector_collection<size_t>(vect1_000, 1000, 1000);
	std::cout << "Average time remove in container of 1000 elements of Vector ::::::" << removeTime1_000.count() << std::endl;

	auto findTime10_000 = time_find_vector_collection<size_t>(vect10_000, 10000, 10000);
	std::cout << "Average time find in container of 10000 elements of Vector ::::::" << findTime10_000.count() << std::endl;


	auto addTime10_000 = time_add_vector_collection<size_t>(vect10_000, 10000, 10000);
	std::cout << "Average time ADD in container of 10000 elements of Vector ::::::" << addTime10_000.count() << std::endl;

	auto removeTime10_000 = time_remove_vector_collection<size_t>(vect10_000, 10000, 10000);
	std::cout << "Average time remove in container of 10000 elements of Vector ::::::" << removeTime10_000.count() << std::endl;

	auto findTime100_000 = time_find_vector_collection<size_t>(vect100_000, 100000, 100000);
	std::cout << "Average time find in container of 100000 elements of Vector ::::::" << findTime100_000.count() << std::endl;


	auto addTime100_000 = time_add_vector_collection<size_t>(vect100_000, 100000, 100000);
	std::cout << "Average time ADD in container of 100000 elements of Vector ::::::" << addTime1_000.count() << std::endl;

	auto removeTime100_000 = time_remove_vector_collection<size_t>(vect100_000, 100000, 100000);
	std::cout << "Average time remove in container of 100000 elements of Vector ::::::" << removeTime100_000.count() << std::endl;
}

void timeTestTree()
{
	BinaryTree<size_t> tree1_000, tree10_000, tree100_000;
	auto time1_000 = time_generate_tree_collection(tree1_000, 100, 1000);
	auto time10_000 = time_generate_tree_collection(tree10_000, 100, 10000);
	auto time100_000 = time_generate_tree_collection(tree100_000, 100, 100000);
	std::cout << "Average time generate 1000 elements of Tree ::::::" << time1_000.count() << std::endl;
	std::cout << "Average time generate 10_000 elements of Tree ::::::" << time10_000.count() << std::endl;
	std::cout << "Average time generate 100_000 elements of Tree ::::::" << time100_000.count() << std::endl;

	auto findTime1_000 = time_find_tree_collection(tree1_000, 1000, 1000);
	auto findTime10_000 = time_find_tree_collection(tree10_000, 1000, 1000);
	auto findTime100_000 = time_find_tree_collection(tree100_000, 1000, 100000);
	std::cout << "Average time find in container of 1000 elements of TREE ::::::" << findTime1_000.count() << std::endl;
	std::cout << "Average time find in container of 10000 elements of TREE ::::::" << findTime10_000.count() << std::endl;
	std::cout << "Average time find in container of 100000 elements of TREE ::::::" << findTime100_000.count() << std::endl;

	auto addTime1_000 = time_add_tree_collection(tree1_000, 1000, 1000);
	auto addTime10_000 = time_add_tree_collection(tree1_000, 10000, 10000);
	auto addTime100_000 = time_add_tree_collection(tree1_000, 100000, 100000);
	std::cout << "Average time ADD in container of 1000 elements of TREE ::::::" << addTime1_000.count() << std::endl;
	std::cout << "Average time ADD in container of 10000 elements of TREE ::::::" << addTime10_000.count() << std::endl;
	std::cout << "Average time ADD in container of 100000 elements of TREE ::::::" << addTime100_000.count() << std::endl;

	auto removeTime1_000 = time_remove_tree_collection(tree1_000, 1000, 1000);
	auto removeTime10_000 = time_remove_tree_collection(tree1_000, 10000, 10000);
	auto removeTime100_000 = time_remove_tree_collection(tree1_000, 100000, 100000);
	std::cout << "Average time remove in container of 1000 elements of TREE ::::::" << removeTime1_000.count() << std::endl;
	std::cout << "Average time remove in container of 10000 elements of TREE ::::::" << removeTime10_000.count() << std::endl;
	std::cout << "Average time remove in container of 100000 elements of TREE ::::::" << removeTime100_000.count() << std::endl;
}

void testTree()
{
	BinaryTree<size_t> tree = BinaryTree<size_t>(8);
	tree.insert(6);
	tree.insert(10);
	tree.insert(4);
	tree.insert(16);
	tree.insert(15);
	tree.insert(14);
	tree.insert(9);
	tree.insert(2);
	tree.insert(7);
	tree.insert(18);

	tree.insert(10);
	tree.insert(15);
	tree.printr();
	std::cout << std::endl;
	std::cout << std::endl;
	tree.remove_norm(10);
	tree.printr();
}


int main()
{
	task_second();
	//tree_test();
	timeTestVector();
	timeTestTree();
}