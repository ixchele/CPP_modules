#include <BitcoinExchange.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

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
		throw BitcoinExchange::FileError("[x] Error : could not open DataBase file \'" + path + "'" + ".");
	
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

// static float parseValue(const std::string& str)
// {
//     std::stringstream ss(str);
//     float value;
//     char c;
//
//     if (!(ss >> value) || (ss >> c))
//         throw BitcoinExchange::BadInput("[x] Error: bad input '" + str + "'.");
//
//     if (value < 0)
//         throw BitcoinExchange::Exception("[x] Error: not a positive number '" + str + "'.");
//
//     if (value > 1000)
//         throw BitcoinExchange::Exception("[x] Error: too large a number '" + str + "'.");
//
//     return value;
// }

static void parseDate(const std::string& s, int& y, int& m, int& d)
{
    std::stringstream ss(s);
    char dash1, dash2;

    if (!(ss >> y >> dash1 >> m >> dash2 >> d) && (dash1 != '-' || dash2 != '-'))
		throw BitcoinExchange::BadInput("[x] Error : invalid date '" + s + "'.");

		//   if ()
		// throw BitcoinExchange::BadInput("[x] Error : invalid date '" + s + "'.");

}

static BitcoinExchange::Data parseLine(std::stringstream &line) {
	std::string	date;
	std::getline(line, date, '|');
	std::cout << date << std::endl;
	return (BitcoinExchange::Data("", 0));
}

BitcoinExchange::DataBase	BitcoinExchange::_loadInputFile(const std::string &path) const {
	std::ifstream	inputFile(path.c_str());
	if (!inputFile.is_open())
		throw BitcoinExchange::FileError("[x] Error : could not open inputFile file \'" + path + "'" + ".");

	DataBase	db;	
	std::string	line;

	std::getline(inputFile, line, '\n');

	while (std::getline(inputFile, line, '\n')) {
		std::stringstream	ss(line);
		parseLine(ss);
	}
	return db;
}

BitcoinExchange::DataBase	BitcoinExchange::getDataBase(void) {
	return _dataBase;
}

void	BitcoinExchange::processFile(const std::string &inputFile) const {
	DataBase	fileContent = _loadInputFile(inputFile);
}
