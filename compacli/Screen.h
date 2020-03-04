#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#include <direct.h>
#endif

class Screen
{
public:
	void init(std::vector<unsigned>& pos, std::string& defFile, std::string& secFile, std::string fn1, std::string fn2);
	void update(unsigned h, unsigned w, unsigned direction);
	void changeFile();

	// Some OS sensitive code
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	void color(char text, WORD color);
	void color(const char* text, WORD color);
	void color(std::string text, WORD color);
	void setWindowSize(int width, int height);
	void changeScreenBuffer(int wayCode);
	void renderVisible();
	void changeTitle();
#endif
#if defined(__linux__)
	void color(char text, unsigned color);
	void color(std::string& text, WORD color);
#endif

	void draw();
private:
	std::pair<unsigned, unsigned> windowSize = std::make_pair(80, 10); // Defaut window size in character
	unsigned curPos = 0; // Current position in file

	std::vector<unsigned> posOfDiff;
	size_t curFile = 0;
	std::vector<std::string> files;
	std::vector<std::string> filenames;
};

