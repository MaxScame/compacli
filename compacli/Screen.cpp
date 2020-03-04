#include "Screen.h"

void Screen::init(std::vector<unsigned>& pos, std::string& defFile, std::string& secFile, std::string fn1, std::string fn2)
{
	// Set some window's params
	setWindowSize(windowSize.first, windowSize.second);

	// Setting default value
	files.push_back(defFile);
	files.push_back(secFile);
	curFile = 0;
	curPos = 0;
	posOfDiff = pos;
	filenames.push_back(fn1);
	filenames.push_back(fn2);
}

void Screen::update(unsigned h, unsigned w, unsigned direction)
{
	
}

void Screen::changeFile()
{
	curFile == 0 ? curFile = 1 : curFile = 0;
}

// Highlighting a line in the console
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
void Screen::color(char Text, WORD Color)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	WORD Attributes = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdout, &Info))
		Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Color);
	std::cout << Text;
	SetConsoleTextAttribute(hStdout, Attributes);
}

void Screen::color(const char* Text, WORD Color)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	WORD Attributes = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdout, &Info))
		Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Color);
	std::cout << Text;
	SetConsoleTextAttribute(hStdout, Attributes);
}

void Screen::color(std::string Text, WORD Color)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	WORD Attributes = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdout, &Info))
		Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Color);
	std::cout << Text;
	SetConsoleTextAttribute(hStdout, Attributes);
}

void Screen::setWindowSize(int width, int height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle 

	// Set default windows size to 0
	SMALL_RECT zeroWindow = { 0, 0, 0, 0 };
	COORD zBuffer = { 1, 1 };
	SetConsoleWindowInfo(handle, TRUE, &zeroWindow);
	SetConsoleScreenBufferSize(handle, zBuffer);

	_COORD coord;
	coord.X = width;
	coord.Y = height;

	_SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	SetConsoleScreenBufferSize(handle, coord); // Set buffer size 
	SetConsoleWindowInfo(handle, TRUE, &rect); // Set window size 
}

void Screen::changeScreenBuffer(int wayCode)
{
	switch (wayCode)
	{
		case 'w': case 72: // Up
		{
			curPos ? curPos-- : curPos;
			std::cout << "UP  " << std::endl;
			break;
		}
		case 'a': case 75: // Left?
		{
			std::cout << "LEFT " << std::endl;
			break;
		}
		case 's': case 80: // Down
		{
			curPos++;
			std::cout << "DOWN " << std::endl;
			break;
		}
		case 'd': case 77: // Right?
		{
			std::cout << "RIGHT" << std::endl;
			break;
		}
	}
}

void Screen::changeTitle()
{
	char Title[1024];
	GetConsoleTitle(Title, 1024); // Get window title
	HWND hwnd = FindWindow(NULL, Title); // Get window's hwnd

	//MoveWindow(hwnd,x,y,width,height,repaint);
	SetConsoleTitle(filenames[curFile].c_str());
}
#endif


#if defined(__linux__)
void Screen::color(char text, unsigned color)
{
	std::cout << "\033[1;31m" << Text << "\033[0m";
}

void Screen::color(std::string& text, unsigned color)
{
	std::cout << "\033[1;31m" << Text << "\033[0m";
}
#endif

void Screen::draw()
{
	changeTitle();
	color("File: ", 63);
	color(filenames[curFile], 63);
	color("     | Line: ", 63);
	color(std::to_string(curPos), 63);
	std::cout << std::endl;
	std::vector<unsigned> pos(posOfDiff);
	for (size_t i = 0; i < files[curFile].length(); i++)
	{
		if (i == pos[0])
		{
			color(files[curFile][i], 63);
			pos.erase(pos.begin(), pos.begin() + 1);
		}
		else
		{
			std::cout << files[curFile][i];
		}
	}
	std::cout << std::endl;
}
