#include "LCD_OS.h"
#include <iostream>

int main(void)
{
	std::cout << "Start main thread" << std::endl;
	return LCD_OS::getLCDOperationSystem().start();
}

