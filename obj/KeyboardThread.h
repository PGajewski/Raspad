#pragma once
#include <thread>
#include <chrono>
#include <atomic>

extern "C"
{
#include "LCD_Key.h"
}

class KeyboardThread : std::thread
{
private:
	KeyboardThread();
	KeyboardThread(const KeyboardThread &) = default;
	KeyboardThread(KeyboardThread &&) = default;

	/*Last event time*/
	std::chrono::time_point<std::chrono::steady_clock> lastEventTime;
	double sleepTime = 20.0;

public:
	/*General change variable*/
	bool wasChange = true;

	bool isDebugKeyboard = true;

	/*Bool variable for each button.*/
	std::atomic_bool isUpKey;
	std::atomic_bool isDownKey;
	std::atomic_bool isLeftKey;
	std::atomic_bool isRightKey;
	std::atomic_bool isPressKey;
	std::atomic_bool isKey1;
	std::atomic_bool isKey2;
	std::atomic_bool isKey3;

	std::atomic_bool isUpKeyEvent;
	std::atomic_bool isDownKeyEvent;
	std::atomic_bool isLeftKeyEvent;
	std::atomic_bool isRightKeyEvent;
	std::atomic_bool isPressKeyEvent;
	std::atomic_bool isKey1Event;
	std::atomic_bool isKey2Event;
	std::atomic_bool isKey3Event;

	static KeyboardThread & getKeyboardThread()
	{
		static KeyboardThread singleton;
		return singleton;
	}
	
	void operator()();

	void updateButtons();

	~KeyboardThread();
};