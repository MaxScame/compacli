#include "Screen.h"

void Screen::init(std::vector<unsigned>& pos, std::string& defFile, std::string& secFile, std::string fn1, std::string fn2)
{
	// Setting default value
	File.push_back(defFile);
	File.push_back(secFile);
	curFile = 0;
	positions = pos;
	filename.push_back(fn1);
	filename.push_back(fn2);
}

void Screen::update()
{
	curFile == 0 ? curFile = 1 : curFile = 0;
}

// Highlighting a line in the console
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
void Screen::color(char Text, WORD Color)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	WORD Attributes;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdout, &Info))
		Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Color);
	std::cout << Text;
	SetConsoleTextAttribute(hStdout, Attributes);
}

void Screen::color(std::string& Text, WORD Color)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	WORD Attributes;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdout, &Info))
		Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Color);
	std::cout << Text;
	SetConsoleTextAttribute(hStdout, Attributes);
}
#endif
#if defined(__linux__)
void Screen::color(char Text, unsigned Color)
{
	std::cout << "\033[1;31m" << Text << "\033[0m";
}

void Screen::color(std::string& Text, unsigned Color)
{
	std::cout << "\033[1;31m" << Text << "\033[0m";
}
#endif

void Screen::draw()
{
	color(filename[curFile], 6);
	std::cout << std::endl;
	std::vector<unsigned> pos(positions);
	size_t posIt = pos.size();
	for (size_t i = 0; i < File[curFile].length(); i++)
	{
		for (size_t j = 0; j < posIt; j++)
		{
			if (i == pos[j])
			{
				color(File[curFile][i], 3);
				pos.erase(pos.begin(), pos.begin() + 1);
				posIt--;
				break;
			}	
			else
			{
				std::cout << File[curFile][i];
				break;
			}
		}
	}
	std::string help = "\nSpace - to change file for view\nq - exit";
	color(help, 6);
}
