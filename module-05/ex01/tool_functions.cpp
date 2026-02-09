#include <asm-generic/ioctls.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <termios.h>
#include <tool_functions.hpp>
#include <unistd.h>
#include <sys/ioctl.h>
#include "colors.h"



struct keyboardLock
{
	termios	oldt;
	bool	active;
	keyboardLock() : active(true) { disable(); }
	~keyboardLock() { enable(); }
	void	disable()
	{
		tcgetattr(STDIN_FILENO, &oldt);
		termios	newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		newt.c_cc[VMIN] = 0;
		newt.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        tcflush(STDIN_FILENO, TCIFLUSH);
		active = true;
	}
	void	enable()
	{
		if (active == false)
			return ;
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        tcflush(STDIN_FILENO, TCIFLUSH);
		active = false;
	}
};

void	enableCursor(void) {
	std::cout << "\033[?25h" << std::flush;
}

void	disableCursor(void) {
	std::cout << "\033[?25l" << std::flush;
}

void	disableLineWrap() {
    std::cout << "\033[7l" << std::flush;
}

void	enableLineWrap() {
    std::cout << "\033[7h" << std::flush;
}

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
	std::cout << "\033[s";
}

void restoreCursor() {
	std::cout << "\033[u";
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
	keyboardLock	lock;
	disableCursor();
    for (std::string::size_type i = 0; i < text.size(); ++i)
    {
        std::cout << text[i] << std::flush;
        usleep(delayUs);
	}
	enableCursor();
}


void	printSlowLines(const std::string &text, unsigned int delayUs)
{
	keyboardLock	lock;
	disableCursor();
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
	enableCursor();
}

void	displayPrompt(void)
{
	clearLine();
	std::cout << "\033[2q";
	std::cout << "❯ ";
}

void	displayMenu(void)
{
	disableCursor();
	enableCursor();
}

void	safeGetLine(std::string &input)
{
	std::getline(std::cin, input);
	if (std::cin.eof())
	{
		input.~basic_string();
		std::exit(1);
	}
}

struct winsize	g_window;

void handle_resize(int sig) {
    (void)sig;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_window) == 0) {
        if (g_window.ws_row < 20 || g_window.ws_col < 60) { 
			disableAlternateScreen();
            std::cout << COLOR_RED "Terminal too small!" COLOR_RESET << std::endl;
			std::exit(1);
        } 
    }
}


static void setRawMode(bool enable, struct termios &oldT) {
	if (enable) {
		tcgetattr(STDIN_FILENO, &oldT);
		struct termios newT = oldT;
		newT.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newT);
	} else {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
	}
}


std::string getSafeInput(const std::string& prompt) {
	struct termios	oldT;
	std::string		input = "";
	char			c;
	struct winsize	w;

	writeTextSlowly(prompt);
	setRawMode(true, oldT);
	while (true) {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		int currentPos = prompt.length() + input.length();

		if (read(STDIN_FILENO, &c, 1) != 1) break;
		if (c == 4) std::exit(1);
		if (c == 27) {
			char next1, next2;
			if (read(STDIN_FILENO, &next1, 1) == 1 && read(STDIN_FILENO, &next2, 1) == 1) {/*pass;*/}
			continue;
		}
		if (c == '\n' || c == '\r') {
			std::cout << std::endl;
			break;
		} 
		else if (c == 127) {
			if (!input.empty()) {
				input.erase(input.size() - 1);
				std::cout << "\b \b" << std::flush;
			}
		} 
		else if (currentPos < w.ws_col - 1) { 
			input += c;
			std::cout << c << std::flush;
		} 
		else {
			std::cout << "\a" << std::flush;
		}
	}
	setRawMode(false, oldT);
	return input;
}
