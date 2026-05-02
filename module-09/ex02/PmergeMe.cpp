#include <PmergeMe.hpp>
#include <cstddef>
#include <utility>
#include <vector>
#include <deque>

unsigned int	g_comp = 0;



//NOTE : less than operator, same as : a < b
bool	ltOperator(int a, int b) {
	return g_comp++, a < b; 
}

bool comparePairs(const intPair& a, const intPair& b) {
    // On compare les 'first' (les gagnants des paires)
    return ltOperator(a.first, b.first);
}

int	JacobsthalSeq(int n) {
	if (n < 2)
		return (n < 1 ? 0 : 1);
	return JacobsthalSeq(n - 1) + 2 * JacobsthalSeq(n - 2);
}

std::vector<intPair>	ParingElements(std::vector<int> &elements, int &straggler) {
	std::vector<intPair>	pairs;

	straggler = -1;
	if (elements.size() % 2 != 0) {
		straggler = elements.back();
		elements.pop_back();
	}

	for (std::size_t i = 0; i < elements.size(); i += 2)
		pairs.push_back(std::make_pair(elements[i], elements[i + 1]));

	return pairs;
}

void	SplitPairs(const std::vector<intPair> pairs, std::vector<int> &largest, std::vector<int> &lowest) {
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		largest.push_back(pairs[i].first);
		lowest.push_back(pairs[i].second);
	}
}

std::vector<int> buildInsertionOrder(int size) {
	std::vector<int>	order;
	if (size == 0)
		return order;

	std::vector<int>	jacob;
	int					j = 0;

	while (true) {
		int	next = JacobsthalSeq(j);
		if (next >= size) {
			jacob.push_back(size);
			break;
		}
		if (next > 1)
			jacob.push_back(next);
		j++;
	}

	int	last = 1;
	for (size_t i = 0; i < jacob.size(); ++i) {
		int	current = jacob[i];
		for (int k = current; k > last; --k) {
			order.push_back(k - 1);
		}
		last = current;
	}
	return order;
}

std::deque<int> buildInsertionOrderDeque(int size) {
	std::deque<int>	order;
	if (size == 0)
		return order;

	std::deque<int>	jacob;
	int					j = 0;

	while (true) {
		int	next = JacobsthalSeq(j);
		if (next >= size) {
			jacob.push_back(size);
			break;
		}
		if (next > 1)
			jacob.push_back(next);
		j++;
	}

	int	last = 1;
	for (size_t i = 0; i < jacob.size(); ++i) {
		int	current = jacob[i];
		for (int k = current; k > last; --k) {
			order.push_back(k - 1);
		}
		last = current;
	}
	return order;
}

int binarySearch(const std::vector<int> &dest, int value, int low, int high) {
	while (low <= high) {
		int	mid = low + (high - low) / 2;

		if (ltOperator(dest[mid], value))
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

int binarySearchDeque(const std::deque<int> &dest, int value, int low, int high) {
	while (low <= high) {
		int	mid = low + (high - low) / 2;

		if (ltOperator(dest[mid], value))
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}
