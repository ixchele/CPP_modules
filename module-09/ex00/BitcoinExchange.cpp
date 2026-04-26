#include <BitcoinExchange.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

BitcoinExchange::BitcoinExchange(void)
: _dataBase(_loadDataBase("./data.csv")), _dbPath("./data.csv") {
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

BitcoinExchange	BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this == &other)
		return *this;
	return *this;
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

std::string trim(const std::string& s) {
	size_t start = s.find_first_not_of(" \t\n\r\f\v");
	if (start == std::string::npos)
		return "";

	size_t end = s.find_last_not_of(" \t\n\r\f\v");

	return s.substr(start, end - start + 1);
}

static bool isLeapYear(int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int daysInMonth(int y, int m) {
	int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	return (m == 2 && isLeapYear(y) ? 29 : days[m - 1]);
}

static bool isValidDate(int y, int m, int d) {
	if (y <= 0)
		return false;

	if (m < 1 || m > 12)
		return false;

	if (d < 1 || d > daysInMonth(y, m))
		return false;

	return true;
}

static void parseDate(const std::string &date)
{
	std::stringstream ss(date);
	char dash1, dash2;
	int y, m, d;

	if (!(ss >> y >> dash1 >> m >> dash2 >> d) && (dash1 != '-' || dash2 != '-'))
		throw BitcoinExchange::BadInput("[x] Error : invalid date format '" + date + "'.");

	if (!isValidDate(y, m, d))
		throw BitcoinExchange::BadInput("[x] Error : invalid date '" + date + "'.");
}

static float	parseValue(const std::string &value) {
	std::stringstream	ss(value);

	float	valuef;
	if (!(ss >> valuef) || !ss.eof())
		throw BitcoinExchange::BadInput("[x] Error : invalid value '" + value + "'.");
	if (valuef > 1000)
		throw BitcoinExchange::BadInput("[x] Error : too large number '" + value + "'.");
	if (valuef < 0)
		throw BitcoinExchange::BadInput("[x] Error : not a positive number '" + value + "'.");

	return valuef;
}

static BitcoinExchange::Data parseLine(std::stringstream &line) {
	std::string	date;
	std::string	value;

	std::getline(line, date, '|');
	std::getline(line, value);
	date = trim(date);
	value = trim(value);

	parseDate(date);
	return (BitcoinExchange::Data(date, parseValue(value)));
}

void	BitcoinExchange::processLine(const Data &data) const {
	std::string	date = data.first;
	float		value = data.second; 

	(void)value;
	DataBase::const_iterator price = _dataBase.lower_bound(date);
	std::cout << date << " => " << value << " = " << (*price).second * value << std::endl;
}

void	BitcoinExchange::processFile(const std::string &filePath) const {
	std::ifstream	inputFile(filePath.c_str());
	if (!inputFile.is_open())
		throw BitcoinExchange::FileError("[x] Error : could not open inputFile file \'" + filePath + "'" + ".");

	std::string	line;

	std::getline(inputFile, line, '\n');

	while (std::getline(inputFile, line, '\n')) {
		std::stringstream	ss(line);
		try {
			Data exctactedData = parseLine(ss);
			processLine(exctactedData);
		} catch (BitcoinExchange::Exception &error) {
			std::cerr << error.what() << std::endl;
		}
	}
}

BitcoinExchange::DataBase	BitcoinExchange::getDataBase(void) {
	return _dataBase;
}
