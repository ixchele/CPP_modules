#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include <PmergeMe.hpp>
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>

void fordJohnsonSort(std::deque<int> &data) {
	if (data.size() <= 1) return;

	int straggler = -1;
	if (data.size() % 2 != 0) {
		straggler = data.back();
		data.pop_back();
	}

	std::deque<intPair> pairs;
	for (size_t i = 0; i < data.size(); i += 2) {
		if (ltOperator(data[i], data[i + 1]))
			pairs.push_back(std::make_pair(data[i + 1], data[i]));
		else
			pairs.push_back(std::make_pair(data[i], data[i + 1]));
	}

	std::deque<int> largests;
	for (size_t i = 0; i < pairs.size(); ++i) 
		largests.push_back(pairs[i].first);

	fordJohnsonSort(largests);

	std::deque<int> pend;
	for (size_t i = 0; i < largests.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (largests[i] == pairs[j].first) {
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}

	largests.insert(largests.begin(), pend[0]);
	std::deque<int> insertionOrder = buildInsertionOrderDeque(pend.size());

	for (size_t i = 0; i < insertionOrder.size(); ++i) {
		int idx = insertionOrder[i];
		if (idx == 0)
			continue; 
		int pos = binarySearchDeque(largests, pend[idx], 0, largests.size() - 1);
		largests.insert(largests.begin() + pos, pend[idx]);
	}

	if (straggler != -1) {
		int pos = binarySearchDeque(largests, straggler, 0, largests.size() - 1);
		largests.insert(largests.begin() + pos, straggler);
	}

	data = largests;
}


void fordJohnsonSort(std::vector<int> &data) {
	if (data.size() <= 1) return;

	int straggler = -1;
	if (data.size() % 2 != 0) {
		straggler = data.back();
		data.pop_back();
	}

	std::vector<intPair> pairs;
	for (size_t i = 0; i < data.size(); i += 2) {
		if (ltOperator(data[i], data[i + 1]))
			pairs.push_back(std::make_pair(data[i + 1], data[i]));
		else
			pairs.push_back(std::make_pair(data[i], data[i + 1]));
	}

	std::vector<int> largests;
	for (size_t i = 0; i < pairs.size(); ++i) 
		largests.push_back(pairs[i].first);

	fordJohnsonSort(largests);

	std::vector<int> pend;
	for (size_t i = 0; i < largests.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (largests[i] == pairs[j].first) {
				pend.push_back(pairs[j].second);
				break;
			}
		}
	}

	largests.insert(largests.begin(), pend[0]);
	std::vector<int> insertionOrder = buildInsertionOrder(pend.size());

	for (size_t i = 0; i < insertionOrder.size(); ++i) {
		int idx = insertionOrder[i];
		if (idx == 0)
			continue; 
		int pos = binarySearch(largests, pend[idx], 0, largests.size() - 1);
		largests.insert(largests.begin() + pos, pend[idx]);
	}

	if (straggler != -1) {
		int pos = binarySearch(largests, straggler, 0, largests.size() - 1);
		largests.insert(largests.begin() + pos, straggler);
	}

	data = largests;
}

int main (int ac, char *av[]) {
	try {
		if (ac != 2)
			throw std::runtime_error("[x] Usage: ./pmg <positive integers>");

		std::vector<int> vec;
		std::deque<int> deq;
		fillContainer(vec, av[1]);
		fillContainer(deq, av[1]);

		struct timeval start, end;

		std::cout << "std::vector" << std::endl;
		std::cout << "Before: ";
		print_range(vec.begin(), vec.end());

		gettimeofday(&start, NULL);
		fordJohnsonSort(vec);
		gettimeofday(&end, NULL);

		std::cout << "After: ";
		print_range(vec.begin(), vec.end());

        std::cout << "Comparisons: " << g_comp << std::endl;

		double timeVec = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

		g_comp = 0;

		std::cout << "std::deque" << std::endl;
		std::cout << "Before: ";
		print_range(vec.begin(), vec.end());

		gettimeofday(&start, NULL);
		fordJohnsonSort(deq);
		gettimeofday(&end, NULL);

		std::cout << "After: ";
		print_range(vec.begin(), vec.end());

        std::cout << "Comparisons: " << g_comp << std::endl;

		double timeDeq = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

		std::cout << "Time to process a range of " << vec.size() 
			<< " elements with std::vector : " << timeVec << " us" << std::endl;
		std::cout << "Time to process a range of " << deq.size() 
			<< " elements with std::deque  : " << timeDeq << " us" << std::endl;

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
