#include "KeyboardThread.h"

void KeyboardThread::operator()()
{
	for (;;)
	{
		updateButtons();
		LCD_OS::getLCDOperationSystem().waitForSignal();
		std::this_thread::sleep_for(100ms);
	}
}

KeyboardThread::~KeyboardThread()
{

}

void KeyboardThread::updateButtons()
{
	//Update key states.
	Listen_Key();

	if (is_up_key) {
		if (!isUpKey.load())
			isUpKeyEvent.store(true);
		isUpKey.store(true);
	}
	else {
		if (isUpKey.load())
			isUpKeyEvent.store(true);
		isUpKey.store(false);
	}

	if (is_down_key) {
		if (!isDownKey.load())
			isDownKeyEvent.store(true);
		isDownKey.store(true);
	}
	else {
		if (isDownKey.load())
			isDownKeyEvent.store(true);
		isDownKey.store(false);
	}

	if (is_left_key) {
		if (!isLeftKey.load())
			isLeftKeyEvent.store(true);
		isLeftKey.store(true);
	}
	else {
		if (isLeftKey.load())
			isLeftKeyEvent.store(true);
		isLeftKey.store(false);
	}

	if (is_right_key) {
		if (!isRightKey.load())
			isRightKeyEvent.store(true);
		isRightKey.store(true);
	}
	else {
		if (isRightKey.load())
			isRightKeyEvent.store(true);
		isRightKey.store(false);
	}

	if (is_press_key) {
		if (!isPressKey.load())
			isPressKeyEvent.store(true);
		isPressKey.store(true);
	}
	else {
		if (isPressKey.load())
			isPressKeyEvent.store(true);
		isPressKey.store(false);
	}

	if (is_key1) {
		if (!isKey1.load())
			isKey1Event.store(true);
		isKey1.store(true);
	}
	else {
		if (isKey1.load())
			isKey1Event.store(true);
		isKey1.store(false);
	}

	if (is_key2) {
		if (!isKey2.load())
			isKey2Event.store(true);
		isKey2.store(true);
	}
	else {
		if (isKey2.load())
			isKey2Event.store(true);
		isKey2.store(false);
	}

	if (is_key3) {
		if (!isKey3.load())
			isKey3Event.store(true);
		isKey3.store(true);
	}
	else {
		if (isKey3.load())
			isKey3Event.store(true);
		isKey3.store(false);
	}

	if (isUpKeyEvent.load() || isDownKeyEvent.load() || isLeftKeyEvent.load() || isRightKeyEvent.load() || isPressKeyEvent.load() || isKey1Event.load() || isKey2Event.load() || isKey3Event.load())
	{
		LCD_OS::getLCDOperationSystem().sendSignal();
		if (isDebugKeyboard)
		{
			//Update LCD screen for new content.
			Show_Debug_Keyboard();
			return;
		}
	}


	if (isUpKey.load() || isDownKey.load() || isLeftKey.load() || isRightKey.load() || isPressKey.load() || isKey1.load() || isKey2.load() || isKey3.load())
	{
		lastEventTime = std::chrono::steady_clock::now();
		isInactive.store(false);
	}
	else {
		auto actualTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = actualTime - lastEventTime;
		if (diff.count() > sleepTime)
		{
			isInactive.store(true);
		}
	}
}