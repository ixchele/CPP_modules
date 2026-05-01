#include <PmergeMe.hpp>

unsigned int	g_comp;

//NOTE : less than operator, same as : a < b
bool	ltOperator(int a, int b) {
	return g_comp++, a < b; 
}

int	JacobsthalSeq(int n) {
	if (n < 2)
		return (n < 1 ? 0 : 1);
	return JacobsthalSeq(n - 1) + 2 * JacobsthalSeq(n - 2);
}


