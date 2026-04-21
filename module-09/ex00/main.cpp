#include "BitcoinExchange.hpp"

int main (int ac, char **av) {
	(void)ac;
	(void)av;

	BitcoinExchange a = BitcoinExchange();
	printMap(a.getDataBase());
	
	return 0;
}
