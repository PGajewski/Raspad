#include "LCD_OS.h"

LCD_OS::LCD:OS()
{
	//Run keyboard handler thread.
	std::thread(this->keyThread);
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
			if (this->keyboardThread.isUpKeyEvent)
			{
				if (this->keyboardThread.isUpKey)
					activeProgram->OnUpKeyPresseed();
				else
					activeProgram->OnUpKeyReleased();
				this->keyboardThread.isUpKeyEvent = false;
			}

			if (this->keyboardThread.isDownKeyEvent)
			{
				if (this->keyboardThread.isDownKey)
					activeProgram->OnDownKeyPresseed();
				else
					activeProgram->OnDownKeyReleased();
				this->keyboardThread.isDownKeyEvent = false;
			}

			if (this->keyboardThread.isLeftKeyEvent)
			{
				if (this->keyboardThread.isLeftKey)
					activeProgram->OnLeftKeyPresseed();
				else
					activeProgram->OnLeftKeyReleased();
			}

			if (this->keyboardThread.isRightKeyEvent)
			{
				if (this->keyboardThread.isRightKey)
					activeProgram->OnRightKeyPresseed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (this->keyboardThread.isRightKeyEvent)
			{
				if (this->keyboardThread.isRightKey)
					activeProgram->OnRightKeyPresseed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (this->keyboardThread.isPressKeyEvent)
			{
				if (this->keyboardThread.isPressKey)
					activeProgram->OnPressKeyPresseed();
				else
					activeProgram->OnPressKeyReleased();
			}

			if (this->keyboardThread.isKey1Event)
			{
				if (this->keyboardThread.isKey1)
					activeProgram->OnKey1Presseed();
				else
					activeProgram->OnKey1Released();
			}

			if (this->keyboardThread.isKey2Event)
			{
				if (this->keyboardThread.isKey2)
					activeProgram->OnKey2Presseed();
				else
					activeProgram->OnKey2Released();
			}

			if (this->keyboardThread.isKey3Event)
			{
				if (this->keyboardThread.isKey3)
					activeProgram->OnKey3Presseed();
				else
					activeProgram->OnKey3Released();
			}
		}
	}
	//3.System Exit
	return 0;
}