#include "LCD_OS.h"

LCD_OS::LCD_OS()
{
	//Run keyboard handler thread.
	std::thread(*this->keyboardThread);
}

LCD_OS::~LCD_OS()
{
	
}

void LCD_OS::setActiveProgram(std::shared_ptr<Program> newProgram, bool wakeOld)
{

}

int LCD_OS::start()
{
	//1.System Initialization
	if (System_Init())
		return(0);

	//2.show
	std::cout << "**********Init LCD**********\r" << std::endl;
	LCD_SCAN_DIR LCD_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
	LCD_Init(LCD_ScanDir);
	LCD_Clear(WHITE);

	for (;;)
	{
		std::thread thr(activeProgram);
		for (;;)
		{
			this->waitForSignal();

			//Modify content of programs.
			if (this->keyboardThread->isUpKeyEvent)
			{
				if (this->keyboardThread->isUpKey)
					activeProgram->OnUpKeyPressed();
				else
					activeProgram->OnUpKeyReleased();
				this->keyboardThread->isUpKeyEvent = false;
			}

			if (this->keyboardThread->isDownKeyEvent)
			{
				if (this->keyboardThread->isDownKey)
					activeProgram->OnDownKeyPressed();
				else
					activeProgram->OnDownKeyReleased();
				this->keyboardThread->isDownKeyEvent = false;
			}

			if (this->keyboardThread->isLeftKeyEvent)
			{
				if (this->keyboardThread->isLeftKey)
					activeProgram->OnLeftKeyPressed();
				else
					activeProgram->OnLeftKeyReleased();
			}

			if (this->keyboardThread->isRightKeyEvent)
			{
				if (this->keyboardThread->isRightKey)
					activeProgram->OnRightKeyPressed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (this->keyboardThread->isRightKeyEvent)
			{
				if (this->keyboardThread->isRightKey)
					activeProgram->OnRightKeyPressed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (this->keyboardThread->isPressKeyEvent)
			{
				if (this->keyboardThread->isPressKey)
					activeProgram->OnPressKeyPressed();
				else
					activeProgram->OnPressKeyReleased();
			}

			if (this->keyboardThread->isKey1Event)
			{
				if (this->keyboardThread->isKey1)
					activeProgram->OnKey1Pressed();
				else
					activeProgram->OnKey1Released();
			}

			if (this->keyboardThread->isKey2Event)
			{
				if (this->keyboardThread->isKey2)
					activeProgram->OnKey2Pressed();
				else
					activeProgram->OnKey2Released();
			}

			if (this->keyboardThread->isKey3Event)
			{
				if (this->keyboardThread->isKey3)
					activeProgram->OnKey3Pressed();
				else
					activeProgram->OnKey3Released();
			}
		}
	}
	//3.System Exit
	return 0;
}