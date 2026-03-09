#include <cstdlib>
#include <iostream>
#include <string>
#include <tool_functions.hpp>


void disableAlternateScreen() {
	std::cout << "\033[?1049l" << std::flush;
}

void enableAlternateScreen() {
	std::cout << "\033[?1049h" << std::flush;
	std::atexit(disableAlternateScreen);
}

void moveTo(int row, int col) {
	std::cout << "\033[" << row << ";" << col << "H";
}

void saveCursor() {
	std::cout << "\033[7";
}

void restoreCursor() {
	std::cout << "\033[8";
	std::cout.flush();
}

void clearFromCursor() {
	std::cout << "\033[J";
}

void clearFromLine(int startRow) {
	moveTo(startRow, 1);
	clearFromCursor();
}

void clearScreen() {
	std::cout << "\033[2J\033[H";
}

void clearLine() {
	std::cout << "\033[2K";
}

void writeTextSlowly(const std::string &text, useconds_t delayUs)

{
    for (std::string::size_type i = 0; i < text.size(); ++i)
    {
        std::cout << text[i] << std::flush;
        usleep(delayUs);
	}
}

void	printSlowLines(const std::string &text, unsigned int delayUs)
{
	std::string line;
	for (std::string::size_type i = 0; i < text.size(); ++i)
	{
		char c = text[i];
		if (c == '\n')
		{
			std::cout << line << std::endl;
			line.clear();
			usleep(delayUs);
		}
		else
			line += c;
	}
	if (!line.empty())
		std::cout << line << std::endl;
}

void	displayPrompt(void)
{
	clearLine();
	std::cout << "\033[2q";
	std::cout << "❯ ";
}

void	displayMenu(void)
{
	std::cout << "\033[?25l";
	printSlowLines(PHONE_BOOK_ART);
	writeTextSlowly(PHONE_BOOK_HELP);
	std::cout << "\033[?25h";
}
