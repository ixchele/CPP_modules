#pragma once
#include <iostream>
#include <colors.h>
#include <unistd.h>
#include <cstdlib>


void	writeTextSlowly(const std::string &text, useconds_t delay_us = 25000);
void	printSlowLines(const std::string &text, unsigned int delayUs = 25000);
void	displayPrompt(void);
void	displayMenu(void);
void	clearScreen(void);
void	clearFromCursor(void);
void	clearFromLine(int);
void	clearLine(void);
void	saveCursor();
void	restoreCursor();
void	moveTo(int, int);
void	enableAlternateScreen();
void	disableAlternateScreen();
void	safeGetLine(std::string &);
