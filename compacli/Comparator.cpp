#include "Comparator.h"


void Comparator::compare(std::string& file1, std::string& file2)
{
	unsigned f1Length = file1.length();
	unsigned f2Length = file2.length();
	unsigned compLength = f1Length > f2Length ? f2Length : f1Length;
	unsigned symbol = 0;
	while (symbol < compLength)
	{
		if (file1[symbol] != file2[symbol])
			positions.push_back(symbol);
		symbol++;
	}
}

const std::vector<unsigned> Comparator::result()
{
	return positions;
}
