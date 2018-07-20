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
	std::thread activeThread;

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

	inline void OS_GUI_DrawLine(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawLine(Xstart, Ystart, Xend, Yend, Color, Line_Style, Dot_Pixel);
		}
	}

	inline void OS_GUI_DrawRectangle(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawRectangle(Xstart, Ystart, Xend, Yend, Color, Filled, Dot_Pixel);
		}
	}


	inline void OS_GUI_DrawCircle(POINT X_Center, POINT Y_Center, LENGTH Radius, COLOR Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DrawCircle(X_Center, Y_Center, Radius, Color, Draw_Fill, Dot_Pixel);
		}
	}

	inline void OS_GUI_Disbitmap(POINT Xpoint, POINT Ypoint, const unsigned char *pBmp, POINT Width, POINT Height)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_Disbitmap(Xpoint, Ypoint, pBmp, Width, Height);
		}
	}

	//Display string

	inline void OS_GUI_DisChar( POINT Xstart, POINT Ystart, const char Acsii_Char, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground)
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisChar(Xstart, Ystart, Acsii_Char, Font, Color_Background, Color_Foreground);
		}
	}

	inline void OS_GUI_DisString_EN(POINT Xstart, POINT Ystart, const char * pString, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisString_EN(Xstart, Ystart, pString, Font, Color_Background, Color_Foreground);
		}
	}

	inline void OS_GUI_DisNum(POINT Xpoint, POINT Ypoint, int32_t Number, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground )
	{
		if(!isOSUsingScreen.load())
		{
			GUI_DisNum(Xpoint, Ypoint, Number, Font, Color_Background, Color_Foreground);
		}
	}

	inline uint8_t OS_LCD_ShowBmp(const char *path)
	{
		if(!isOSUsingScreen.load())
		{
			LCD_ShowBmp(path);
		}
	}

	inline void OS_LCD_Clear(COLOR Color)
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

	inline void OS_LCD_SetWindows( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend )
	{
		if(!isOSUsingScreen.load())
		{
			LCD_SetWindows(Xstart, Ystart, Xend, Yend);
		}
	}

	inline void OS_LCD_SetCursor ( POINT Xpoint, POINT Ypoint )
	{
		if(!isOSUsingScreen.load())
		{
			LCD_SetCursor(Xpoint, Ypoint);
		}
	}

	inline void OS_LCD_SetColor( COLOR Color ,POINT Xpoint, POINT Ypoint)
	{
		if(!isOSUsingScreen.load())
		{
			LCD_SetColor(Color, Xpoint, Ypoint);
		}
	}

	inline void OS_LCD_SetPointlColor ( POINT Xpoint, POINT Ypoint, COLOR Color )
	{
		if(!isOSUsingScreen.load())
		{
			LCD_SetPointlColor(Xpoint, Ypoint, Color);
		}
	}

	inline void OS_LCD_SetArealColor ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend,COLOR  Color)
	{
		if(!isOSUsingScreen.load())
		{
			LCD_SetArealColor(Xstart, Ystart, Xend, Yend, Color);
		}
	}

	void setActiveProgram(std::shared_ptr<Program> newProgram, bool wakeOld);

	~LCD_OS();
};

