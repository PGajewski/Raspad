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
	std::atomic_bool isOSUsingScreen{false};	
	std::thread keyboardThread;

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
	
	inline void GUI_DrawLine(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawLine(Xstart, Ystart, Xend, Yend, Color, Line_style, Dot_Pixel);
		}
	}

	inline void GUI_DrawRectangle(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawRectangle(Xstart, Ystart, Xend, Yend, Color, Filled, Dot_Pixel);
		}
	}


	inline void GUI_DrawCircle(POINT X_Center, POINT Y_Center, LENGTH Radius, COLOR Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawCirce(X_Center, Y_Center, Radius, Color, Draw_Fill, Dot_Pixel);
		}
	}

	inline void GUI_Disbitmap(POINT Xpoint, POINT Ypoint, const unsigned char *pBmp, POINT Width, POINT Height)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_Disbitman(Xpoint, Ypoint, Width, Height);
		}
	}

	//Display string

	inline void GUI_DisChar( POINT Xstart, POINT Ystart, const char Acsii_Char, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisChar(Xstart, Ystart, Acsii_Char, Font, Color_Background, Color_Foreground);
		}
	}

	inline void GUI_DisString_EN(POINT Xstart, POINT Ystart, const char * pString, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisString(Xstart, Ystart, pString, Font, Color_Background, Color_Foreground);
		}
	}

	inline void GUI_DisNum(POINT Xpoint, POINT Ypoint, int32_t Nummber, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisNum(Xpoint, Ypoint, Number, Font, Color_Background, Color_Foreground);
		}
	}

	inline uint8_t LCD_ShowBmp(const char *path)
	{
		if(!isOSUsingScreen.load())
		{
			LCD_ShowBmp(path);
		}
	}

	inline void LCD_Clear(COLOR  Color)
	{
		if (!isOSUsingScreen.load())
		{
			LCD_Clear(Color);
		}
	}


	inline void returnToMainProgram()
	{
		sleepingProgramsList.push_back(activeProgram);
		activeProgram = mainProgram;
	}

	void setActiveProgram(std::shared_ptr<Program> newProgram, bool wakeOld);

	~LCD_OS();
};

