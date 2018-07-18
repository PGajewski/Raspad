extern "C" {
#include <bcm2835.h>
#include "DEV_Config.h"
#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_Key.h"
}

#include <iostream>

int main(void)
{
	//1.System Initialization
	if(System_Init())
		return(0);

	//2.show
	std::cout << "**********Init LCD**********\r" << std::endl;
	LCD_SCAN_DIR LCD_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
	LCD_Init(LCD_ScanDir );
	LCD_Clear(WHITE);

	Start_Keyboard_Thread();

	Keyboard_Thread_Join();

	//3.System Exit
	return 0;

}

