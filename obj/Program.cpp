#include "Program.h"
#include "LCD_OS.h"

void Program::OnLeftKeyPressed()
{
	//Do nothing
}

void Program::OnLeftKeyReleased()
{
	//Do nothing
}

void Program::OnRightKeyPressed()
{
	//Do nothing
}

void Program::OnRightKeyReleased()
{
	//Do nothing
}

void Program::OnUpKeyPressed()
{
	//Do nothing
}

void Program::OnUpKeyReleased()
{
	//Do nothing
}

void Program::OnDownKeyPressed()
{
	//Do nothing
}
void Program::OnDownKeyReleased()
{
	//Do nothing
}

void Program::OnPressKeyPressed()
{
	//Do nothing
}
void Program::OnPressKeyReleased()
{
	//Do nothing
}

void Program::OnKey1Pressed()
{
	//Do nothing
}

void Program::OnKey1Released()
{
	//Do nothing
}

void Program::OnKey2Pressed()
{
	LCD_OS::getLCDOperationSystem().returnToMainProgram();
	running.store(false);
	LCD_OS::getLCDOperationSystem().sendSignal();

}

void Program::OnKey2Released()
{
	//Do nothing
}

void Program::OnKey3Pressed()
{
	//Do nothing
}

void Program::OnKey3Released()
{
	//Do nothing
}

void Program::OnExit()
{

}

void Program::OnSleep()
{

}

/*Thread function - virtual*/
void Program::operator()()
{
	while (running.load())
	{
		//Default test thread.
		LCD_OS::getLCDOperationSystem().OS_LCD_Clear(GUI_BACKGROUND);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		LCD_OS::getLCDOperationSystem().OS_LCD_Clear(RED);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
