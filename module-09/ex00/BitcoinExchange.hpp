#pragma once
#include <map>
#include <stdexcept>
#include <string>

class	BitcoinExchange {
	public:
		typedef	std::map<std::string, float> DataBase;
		typedef	std::pair<std::string, float> Data;
	private:

		const DataBase		_dataBase;
		const std::string	_dbPath;

		DataBase	_loadDataBase(const std::string &dbPath) const;

	public:

		BitcoinExchange(void);
		BitcoinExchange(const std::string &dbPath);
		BitcoinExchange(const BitcoinExchange &other);

		~BitcoinExchange(void);
		
		BitcoinExchange	operator=(const BitcoinExchange &other);
		
		DataBase	getDataBase(void);

		void	processFile(const std::string &inputFile) const;
		void	processLine(const Data &data) const;

		struct	Exception : public std::runtime_error {
			Exception(const std::string &error) : std::runtime_error(error) {};
		};

		struct	FileError : public Exception {
			FileError(const std::string &error) : Exception(error) {};
		};

		struct	BadInput : public Exception {
			BadInput(const std::string &error) : Exception(error) {};
		};

		struct	NegativeNumber : public Exception {
			NegativeNumber(const std::string &error) : Exception(error) {};
		};
		
		struct	TooLargeNumber : public Exception {
			TooLargeNumber(const std::string &error) : Exception(error) {};
		};
};
