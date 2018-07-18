#include "LCD_Key.h"
#include "LCD_GUI.h"
#include "LCD_BMP.h"
#include "DEV_Config.h"
#include "time.h"
#include <pthread.h>

#define SLEEP_TIME 10

bool is_left_key = false;
bool is_right_key = false;
bool is_up_key = false;
bool is_down_key = false;
bool is_press_key = false;
bool is_key1 = false;
bool is_key2 = false;
bool is_key3 = false;

bool is_debug_keyboard = true;

static bool was_changed = true;

static pthread_t keyboard_thread;

void Show_Debug_Keyboard(void)
{

        if(is_up_key){
        	GUI_DrawRectangle(30, 19, 60, 49, RED, DRAW_FULL, DOT_PIXEL_DFT);
        } else {
        	GUI_DrawRectangle(30, 19, 60, 49, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(40, 28, "U", &Font16, GUI_BACKGROUND, BLUE);


        if(is_down_key){
                GUI_DrawRectangle(30, 79, 60, 109, RED, DRAW_FULL, DOT_PIXEL_DFT);
        } else {
                GUI_DrawRectangle(30, 79, 60, 109, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(40, 88, "D", &Font16, GUI_BACKGROUND, BLUE);


        if(is_left_key){
                GUI_DrawRectangle(0, 49, 30, 79, RED, DRAW_FULL, DOT_PIXEL_DFT);
	} else {
                GUI_DrawRectangle(0, 49, 30, 79, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(10, 58, "L", &Font16, GUI_BACKGROUND, BLUE);


       	if(is_right_key){
                GUI_DrawRectangle(60, 49, 90, 79, RED, DRAW_FULL, DOT_PIXEL_DFT);
       	} else {
                GUI_DrawRectangle(60, 49, 90, 79, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(70, 58, "R", &Font16, GUI_BACKGROUND, BLUE);


       	if(is_press_key){
               GUI_DrawCircle(45, 64, 15, RED, DRAW_FULL, DOT_PIXEL_DFT);
       	} else {
               GUI_DrawCircle(45, 64, 15, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(40, 58, "P", &Font16, GUI_BACKGROUND, BLUE);


       	if(is_key1){
               GUI_DrawRectangle(95, 20, 125, 45, RED, DRAW_FULL, DOT_PIXEL_DFT);
   	} else {
               GUI_DrawRectangle(95, 20, 125, 45, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(100, 27, "K1", &Font16, GUI_BACKGROUND, BLUE);


	if(is_key2){
               GUI_DrawRectangle(95, 52, 125, 78, RED, DRAW_FULL, DOT_PIXEL_DFT);
        } else {
               GUI_DrawRectangle(95, 52, 125, 78, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(100, 59, "K2", &Font16, GUI_BACKGROUND, BLUE);

        if(is_key3){
               GUI_DrawRectangle(95, 85, 125, 110, RED, DRAW_FULL, DOT_PIXEL_DFT);
        } else {
               GUI_DrawRectangle(95, 85, 125, 110, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
	}
        GUI_DisString_EN(100, 92, "K3", &Font16, GUI_BACKGROUND, BLUE);

}

void* Listen_Key(void* params)
{
	struct timespec last_press, actual_press;
	clock_gettime(CLOCK_REALTIME, &last_press);
	for(;;)
	{
		if(GET_KEY_UP == 0){
			if(!is_up_key)
				was_changed = true;
			is_up_key = true;
		} else {
			if(is_up_key)
				was_changed = true;
			is_up_key = false;
		}

		if(GET_KEY_DOWN == 0){
			if(!is_down_key)
				was_changed = true;
			is_down_key = true;
		} else {
			if(is_down_key)
				was_changed = true;
			is_down_key = false;
		}

		if(GET_KEY_LEFT == 0){
			if(!is_left_key)
				was_changed = true;
			is_left_key = true;
		} else {
			if(is_left_key)
				was_changed = true;
			is_left_key = false;
		}

		if(GET_KEY_RIGHT == 0){
			if(!is_right_key)
				was_changed = true;
			is_right_key = true;
		} else {
			if(is_right_key)
				was_changed = true;
			is_right_key = false;
		}

		if(GET_KEY_PRESS == 0){
			if(!is_press_key)
				was_changed = true;
			is_press_key = true;
		} else {
			if(is_press_key)
				was_changed = true;
			is_press_key = false;
		}

		if(GET_KEY1 == 0){
			if(!is_key1)
				was_changed = true;
			is_key1 = true;
		} else {
			if(is_key1)
				was_changed = true;
			is_key1 = false;
		}

		if(GET_KEY2 == 0){
			if(!is_key2)
				was_changed = true;
			is_key2 = true;
		} else {
			if(is_key2)
				was_changed = true;
			is_key2 = false;
		}

		if(GET_KEY3 == 0){
			if(!is_key3)
				was_changed = true;
			is_key3 = true;
		} else {
			if(is_key3)
				was_changed = true;
			is_key3 = false;
		}


                if(is_debug_keyboard && was_changed)
                {
                        LCD_Clear(GUI_BACKGROUND);
                        was_changed = false;
                        Show_Debug_Keyboard();
			Driver_Delay_ms(500);
			continue;
                }


                if(is_up_key || is_down_key || is_left_key || is_right_key || is_press_key || is_key1 || is_key2 || is_key3)
                {
                        clock_gettime(CLOCK_REALTIME, &last_press);
                } else {
                        clock_gettime(CLOCK_REALTIME, &actual_press);
                        if((actual_press.tv_sec - last_press.tv_sec)  > SLEEP_TIME)
                        {
                                LCD_ShowBmp("/raspad/pic/logo.bmp");
                        }
		}

        	Driver_Delay_ms(500);
	}
}

bool Start_Keyboard_Thread(void)
{
	if(pthread_create(&keyboard_thread, NULL, Listen_Key, NULL))
	{
		printf("Cannot run keyboard thread");
		return false;
	}
	return true;
}

void Keyboard_Thread_Join(void)
{
	void* ret = NULL;
	if(pthread_join(keyboard_thread, &ret))
		printf("Error with joining keyboard thread");
}
