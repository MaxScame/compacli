#include <iostream>
#include <memory>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <conio.h>
#define getch() _getch()
#define clearScreen() system("cls")
#endif

#include "File.h"
#include "Screen.h"
#include "Comparator.h"


#if defined(__linux__)
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

int getch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

#define clearScreen() std::system("clear")
#endif

namespace help
{
	void show()
	{
		std::cout << "Commands:\n --help - Help\n" << std::endl;
		std::cout << "Usage:\n [./]complicli[.exe] file1 file2" << std::endl;
		getch();
	}
}



int main(int argc, char* argv[])
{
	std::string filename1;
	std::string filename2;
	if (argv[1] == "--help" || argc == 1)
	{
		help::show();
		return 0;
	}

	if (argc == 3)
	{
		filename1 = argv[1];
		filename2 = argv[2];
	}

	clearScreen();

	File f;
	std::string f1 = f.get(filename1);
	std::string f2 = f.get(filename2);
	std::unique_ptr<Comparator> cp = std::make_unique<Comparator>();
	cp.get()->compare(f1, f2);
	std::vector<unsigned> positions(cp.get()->result());
	std::unique_ptr<Screen> sc = std::make_unique<Screen>();
	sc.get()->init(positions, f1, f2, filename1, filename2/*argh!!!*/);
	sc.get()->draw();
	positions.clear();
	while (true)
	{
		int keyPressed = 0;
		while (keyPressed != ' ')
		{
			keyPressed = getch();
			if (keyPressed == 'q')
				return 0;
		}
		sc.get()->update();
		clearScreen(); // Clear screen
		sc.get()->draw();
	}
	return 0;
}