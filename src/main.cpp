#include <iostream>

#include "PipeLine.h"

int main()
{
	PipeLine * pipeLine = new PipeLine();

	pipeLine->load();

	delete pipeLine;

	std::cout << std::endl;
	std::cout << "Insert any character to quit> ";
	std::getchar();
	return 0;
}
