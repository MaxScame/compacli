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
	void update();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	void color(char Text, WORD Color);
	void color(std::string& Text, WORD Color);
#endif
#if defined(__linux__)
	void color(char Text, unsigned Color);
	void color(std::string& Text, WORD Color);
#endif
	void draw();
private:
	std::vector<unsigned> positions;
	size_t curFile;
	std::vector<std::string> File;
	std::vector<std::string> filename;
};

