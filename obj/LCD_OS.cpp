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
			if (KeyboardThread::getKeyboardThread.isUpKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isUpKey)
					activeProgram->OnUpKeyPressed();
				else
					activeProgram->OnUpKeyReleased();
				KeyboardThread::getKeyboardThread.isUpKeyEvent = false;
			}

			if (KeyboardThread::getKeyboardThread.isDownKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isDownKey)
					activeProgram->OnDownKeyPressed();
				else
					activeProgram->OnDownKeyReleased();
				KeyboardThread::getKeyboardThread.isDownKeyEvent = false;
			}

			if (KeyboardThread::getKeyboardThread.isLeftKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isLeftKey)
					activeProgram->OnLeftKeyPressed();
				else
					activeProgram->OnLeftKeyReleased();
			}

			if (KeyboardThread::getKeyboardThread.isRightKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isRightKey)
					activeProgram->OnRightKeyPressed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (KeyboardThread::getKeyboardThread.isRightKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isRightKey)
					activeProgram->OnRightKeyPressed();
				else
					activeProgram->OnRightKeyReleased();
			}

			if (KeyboardThread::getKeyboardThread.isPressKeyEvent)
			{
				if (KeyboardThread::getKeyboardThread.isPressKey)
					activeProgram->OnPressKeyPressed();
				else
					activeProgram->OnPressKeyReleased();
			}

			if (KeyboardThread::getKeyboardThread.isKey1Event)
			{
				if (KeyboardThread::getKeyboardThread.isKey1)
					activeProgram->OnKey1Pressed();
				else
					activeProgram->OnKey1Released();
			}

			if (KeyboardThread::getKeyboardThread.isKey2Event)
			{
				if (KeyboardThread::getKeyboardThread.isKey2)
					activeProgram->OnKey2Pressed();
				else
					activeProgram->OnKey2Released();
			}

			if (KeyboardThread::getKeyboardThread.isKey3Event)
			{
				if (KeyboardThread::getKeyboardThread.isKey3)
					activeProgram->OnKey3Pressed();
				else
					activeProgram->OnKey3Released();
			}
		}
	}
	//3.System Exit
	return 0;
}