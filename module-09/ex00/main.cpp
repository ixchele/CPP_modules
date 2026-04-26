#include "BitcoinExchange.hpp"

int main (int ac, char **av) {
	if (ac != 2)
		return (std::cout << "[!] Usage : ./btc <inputFile>", -1);

	BitcoinExchange a = BitcoinExchange();
	a.processFile(av[1]);

	return 0;
}
