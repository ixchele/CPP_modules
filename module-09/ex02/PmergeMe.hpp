#pragma once

#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <limits>

typedef std::pair<int, int> intPair;

extern	unsigned int g_comp;

unsigned int			JacobsthalSeq(unsigned int n);
void					fordJohnsonSort(std::vector<int> &data);
std::vector<intPair>	ParingElements(std::vector<int> &elements, int &straggler);
bool					ltOperator(int a, int b);
void					SplitPairs(const std::vector<intPair> pairs, std::vector<int> &largest, std::vector<int> &lowest);
std::vector<int>		buildInsertionOrder(int size);
std::deque<int>			buildInsertionOrderDeque(int size);
int						binarySearch(const std::vector<int> &dest, int value, int low, int high);
int						binarySearchDeque(const std::deque<int> &dest, int value, int low, int high);
bool					comparePairs(const intPair& a, const intPair& b);


// NOTE : for debuging
template <typename T>
void print_pairs(const std::vector<std::pair<T, T> >& couples) {
	std::cout << "[ ";
	for (size_t i = 0; i < couples.size(); ++i) {
		std::cout << "(" << couples[i].first << ", " << couples[i].second << ") ";
	}
	std::cout << "]" << std::endl;
}

template <typename InputIterator>
void print_range(InputIterator first, InputIterator last) {
	std::cout << "[ ";
	while (first != last) {
		std::cout << *first << " ";
		++first;
	}
	std::cout << "]" << std::endl;
}

template <typename Container>
void	fillContainer(Container &container, const std::string &input) {
	if (input.empty())
		throw std::runtime_error("Error");

	std::stringstream	ssInput(input);
	long				number = 0;	
	std::set<int>		seen;

	while (1) {
		ssInput >> number;

		if (ssInput.fail())
			break;

		if (number < 0 || number > std::numeric_limits<int>::max())
			throw std::runtime_error("Error");

		if (!seen.insert(static_cast<int>(number)).second)
					throw std::runtime_error("Error");

		container.push_back(number);
	}

	if (!ssInput.eof())
		throw std::runtime_error("Error");
}


template <typename T>
void sortingPairs(T &pairs) {
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		if (ltOperator(pairs[i].first, pairs[i].second))
			std::swap(pairs[i].first, pairs[i].second);
	}
}

