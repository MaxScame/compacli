#pragma once
#include <memory>
#include <vector>
#include <string>

class Comparator
{
public:
	void compare(std::string& file1, std::string& file2);
	const std::vector<unsigned> result();
private:
	std::vector<unsigned> positions;
	std::vector<std::string> f1;
	std::vector<std::string> f2;
};

