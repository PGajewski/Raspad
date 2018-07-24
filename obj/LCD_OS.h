#pragma once
#include "Program.h"
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "MainScreen.h"
#include "KeyboardThread.h"

extern "C"
{
#include <bcm2835.h>
#include "DEV_Config.h"
#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_BMP.h"
}

using namespace std::chrono_literals;

class LCD_OS
{
private:
	LCD_OS();

	/*Condition variable*/
	std::condition_variable cv;
	std::mutex mx;

	/*Programs active in OS*/
	std::shared_ptr<Program> mainProgram = std::make_shared<MainProgram>();
	std::shared_ptr<Program> activeProgram = std::make_shared<MainProgram>();
	std::vector<std::shared_ptr<Program>> sleepingProgramsList;

public:
	static LCD_OS & getLCDOperationSystem()
	{
		static LCD_OS singleton;
		return singleton;
	}
	int start();
	
	LCD_OS(LCD_OS const&) = delete;
	void operator=(LCD_OS const&) = delete; // Don't implement

	inline void waitForSignal()
	{
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [] {return true; });
	}

	inline void sendSignal()
	{
		cv.notify_one();
	}

	void setActiveProgram(std::shared_ptr<Program> newProgram, bool wakeOld);

	~LCD_OS();
};