#include "LCD_OS.h"

LCD_OS::LCD_OS()
{
	//Run keyboard handler thread.
	std::thread(KeyboardThread::getKeyboardThread());
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

			//Check inactive.
			if (KeyboardThread::getKeyboardThread().isInactive.load())
			{
				LCD_ShowBmp("/raspad/pic/logo.bmp");
			}

			//Modify content of programs.
			if (KeyboardThread::getKeyboardThread().isUpKeyEvent.load())
			{
				if (KeyboardThread::getKeyboardThread().isUpKey.load())
					activeProgram->OnUpKeyPressed();
				else
					activeProgram->OnUpKeyReleased();
				KeyboardThread::getKeyboardThread().isUpKeyEvent.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isDownKeyEvent.load())
			{
				if (KeyboardThread::getKeyboardThread().isDownKey.load())
					activeProgram->OnDownKeyPressed();
				else
					activeProgram->OnDownKeyReleased();
				KeyboardThread::getKeyboardThread().isDownKeyEvent.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isLeftKeyEvent.load())
			{
				if (KeyboardThread::getKeyboardThread().isLeftKey.load())
					activeProgram->OnLeftKeyPressed();
				else
					activeProgram->OnLeftKeyReleased();
				KeyboardThread::getKeyboardThread().isLeftKeyEvent.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isRightKeyEvent.load())
			{
				if (KeyboardThread::getKeyboardThread().isRightKey.load())
					activeProgram->OnRightKeyPressed();
				else
					activeProgram->OnRightKeyReleased();
				KeyboardThread::getKeyboardThread().isRightKeyEvent.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isPressKeyEvent.load())
			{
				if (KeyboardThread::getKeyboardThread().isPressKey.load())
					activeProgram->OnPressKeyPressed();
				else
					activeProgram->OnPressKeyReleased();
				KeyboardThread::getKeyboardThread().isPressKeyEvent.store(false);

			}

			if (KeyboardThread::getKeyboardThread().isKey1Event.load())
			{
				if (KeyboardThread::getKeyboardThread().isKey1.load())
					activeProgram->OnKey1Pressed();
				else
					activeProgram->OnKey1Released();
				KeyboardThread::getKeyboardThread().isKey1Event.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isKey2Event.load())
			{
				if (KeyboardThread::getKeyboardThread().isKey2.load())
					activeProgram->OnKey2Pressed();
				else
					activeProgram->OnKey2Released();
				KeyboardThread::getKeyboardThread().isKey2Event.store(false);
			}

			if (KeyboardThread::getKeyboardThread().isKey3Event.load())
			{
				if (KeyboardThread::getKeyboardThread().isKey3.load())
					activeProgram->OnKey3Pressed();
				else
					activeProgram->OnKey3Released();
				KeyboardThread::getKeyboardThread().isKey3Event.store(false);
			}
		}
	}
	//3.System Exit
	return 0;
}