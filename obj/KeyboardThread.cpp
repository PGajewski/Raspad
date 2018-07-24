#include "KeyboardThread.h"
#include "LCD_OS.h"

void KeyboardThread::operator()()
{
	for (;;)
	{
		updateButtons();
		LCD_OS::getLCDOperationSystem().waitForSignal();
		sleep_for(100ms);
	}
}

void KeyboardThread::updateButtons()
{
	//Update key states.
	Listen_Key();

	if (is_up_key) {
		if (!isUpKey)
			isUpKeyEvent = true;
		isUpKey = true;
	}
	else {
		if (isUpKey)
			isUpKeyEvent = true;
		isUpKey = false;
	}

	if (is_down_key) {
		if (!isDownKey)
			isDownKeyEvent = true;
		isDownKey = true;
	}
	else {
		if (isDownKey)
			isDownKeyEvent = true;
		isDownKey = false;
	}

	if (is_left_key) {
		if (!isLeftKey)
			isLeftKeyEvent = true;
		isLeftKey = true;
	}
	else {
		if (isLeftKey)
			isLeftKeyEvent = true;
		isLeftKey = false;
	}

	if (is_right_key) {
		if (!isRightKey)
			isRightKeyEvent = true;
		isRightKey = true;
	}
	else {
		if (isRightKey)
			isRightKeyEvent = true;
		isRightKey = false;
	}

	if (is_press_key) {
		if (!isPressKey)
			isPressKeyEvent = true;
		isPressKey = true;
	}
	else {
		if (isPressKey)
			isPressKeyEvent = true;
		isPressKey = false;
	}

	if (is_key1) {
		if (!isKey1)
			isKey1Event = true;
		isKey1 = true;
	}
	else {
		if (isKey1)
			isKey1Event = true;
		isKey1 = false;
	}

	if (is_key2) {
		if (!isKey2)
			isKey2Event = true;
		isKey2 = true;
	}
	else {
		if (isKey2)
			isKey2Event = true;
		isKey2 = false;
	}

	if (is_key3) {
		if (!isKey3)
			isKey3Event = true;
		isKey3 = true;
	}
	else {
		if (isKey3)
			isKey3Event = true;
		isKey3 = false;
	}

	if (isUpKeyEvent || isDownKeyEvent || isLeftKeyEvent || isRightKeyEvent || isPressKeyEvent || isKey1Event || isKey2Event || isKey3Event)
	{
		LCD_OS.getLCDOperationSystem().sendSignal();
		if (is_debug_keyboard)
		{
			//Update LCD screen for new content.
			Show_Debug_Keyboard();
			return;
		}
	}


	if (isUpKey || isDownKey || isLeftey || isRightKey || isPressKey || isKey1 || isKey2 || isKey3)
	{
		lastEventTime = std::chrono::steady_clock::now();
	}
	else {
		auto actualTime = auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = actualTime - lastEventTime;
		if ((diff.count)  > sleepTime)
		{
			LCD_ShowBmp("/raspad/pic/logo.bmp");
		}
	}
}