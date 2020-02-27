#include "File.h"

std::string File::get(std::string filename)
{
	std::fstream file(filename, std::ios::binary | std::ios::in);
	if (!file.is_open())
	{
		std::string empty = "";
		std::cout << "Error in opening file: " << filename << std::endl;
		return empty;
	}
	std::string data(std::istreambuf_iterator<char>(file), {});
	file.close();
	return data;
}