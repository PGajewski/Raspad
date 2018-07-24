#pragma once
#include <thread>
#include <chrono>
#include <atomic>

extern "C"
{
#include "LCD_Key.h"
}
using namespace std::chrono_literals;

class KeyboardThread : std::thread
{
private:
	KeyboardThread();

	/*Last event time*/
	std::chrono::time_point<std::chrono::steady_clock> lastEventTime;
	double sleepTime = 20.0;

public:
	/*General change variable*/
	bool wasChange = true;

	bool isDebugKeyboard = true;

	KeyboardThread(KeyboardThread const&) = delete;
	void operator=(KeyboardThread const&) = delete; // Don't implement

	/*Bool variable for each button.*/
	std::atomic_bool isUpKey{ false };
	std::atomic_bool isDownKey{false};
	std::atomic_bool isLeftKey{false};
	std::atomic_bool isRightKey{false};
	std::atomic_bool isPressKey{false};
	std::atomic_bool isKey1{false};
	std::atomic_bool isKey2{false};
	std::atomic_bool isKey3{false};

	std::atomic_bool isUpKeyEvent{true};
	std::atomic_bool isDownKeyEvent{true};
	std::atomic_bool isLeftKeyEvent{true};
	std::atomic_bool isRightKeyEvent{true};
	std::atomic_bool isPressKeyEvent{true};
	std::atomic_bool isKey1Event{true};
	std::atomic_bool isKey2Event{true};
	std::atomic_bool isKey3Event{true};

	static KeyboardThread & getKeyboardThread()
	{
		static KeyboardThread singleton;
		return singleton;
	}
	
	void operator()();

	void updateButtons();

	~KeyboardThread();
};