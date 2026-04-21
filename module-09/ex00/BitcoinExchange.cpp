#include <BitcoinExchange.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

BitcoinExchange::BitcoinExchange(void)
	: _dataBase(_loadDataBase("./data.csv")), _dbPath("./data.csv"){
	//pass
}

BitcoinExchange::BitcoinExchange(const std::string &dbPath)
	: _dataBase(_loadDataBase(dbPath)), _dbPath(dbPath) {
	//pass
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _dataBase(_loadDataBase(other._dbPath)), _dbPath(other._dbPath) {
	//pass
}

BitcoinExchange::~BitcoinExchange(void) {
	//pass
}

BitcoinExchange::DataBase	BitcoinExchange::_loadDataBase(const std::string &path) const {
	std::ifstream	dbFile(path.c_str());
	if (!dbFile.is_open())
		throw BitcoinExchange::FileError("[x] Error : could not open DataBase file " + path + ".");
	
	DataBase	db;	
	std::string	line;

	std::getline(dbFile, line, '\n');

	while (std::getline(dbFile, line, '\n')) {
		std::stringstream	ss(line);

		std::string	date;
		std::string	value;

		std::getline(ss, date, ',');
		std::getline(ss, value);

		db[date] = std::strtof(value.c_str(), NULL);
	}
	return db;
}	

BitcoinExchange::DataBase	BitcoinExchange::getDataBase(void) {
	return _dataBase;
}
