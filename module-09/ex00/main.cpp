#include "BitcoinExchange.hpp"
#include <sstream>
#include <string>

int main (int ac, char **av) {
	(void)ac;
	(void)av;

	BitcoinExchange a = BitcoinExchange();
	a.processFile("./input.txt");

	
	return 0;
}
