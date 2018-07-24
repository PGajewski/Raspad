#pragma once
#include "Program.h"
#include <vector>
#include <memory>
#include "KeyboardThread.h"
#include <mutex>
#include <condition_variable>
#include <iostream>

extern "C"
{
#include <bcm2835.h>
#include "DEV_Config.h"
#include "LCD_Driver.h"
#include "LCD_GUI.h"
}

class LCD_OS
{
private:
	LCD_OS();
	LCD_OS(const LCD_OS &) = default;
	LCD_OS(LCD_OS &&) = default;
	/*Keyboard events thread*/
	std::thread keyboardThread = KeyboardThread.getKeyboardThread();

	/*Condition variable*/
	std::condition_variable cv;
	std::mutex mx;

	/*Programs active in OS*/
	std::shared_ptr<Program> mainProgram;
	std::shared_ptr<Program> activeProgram;
	std::vector<std::shared_ptr<Program>> sleepingProgramsList;

public:
	static LCD_OS & getLCDOperationSystem()
	{
		static LCD_OS singleton;
		return singleton;
	}
	int start();
	
	inline void waitForSignal()
	{
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [] {return true; });
	}

	inline void sendSignal()
	{
		cv.notify_one();
	}

	void setActiveProgram(std::shared_ptr<Program> newProgram, bool wakeOld)
	{
		//Looking for old program instance in sleeping vector.
		this->sleepingProgramsList.push_back(activeProgram)
	}

	~LCD_OS();
};