#include <stdbool.h>

#ifndef _LCD_SNAKE_H_
#define _LCD_SNAKE_H_

//Extern key boolean variable
extern bool is_left_key;
extern bool is_right_key;
extern bool is_up_key;
extern bool is_down_key;
extern bool is_press_key;
extern bool is_key1;
extern bool is_key2;
extern bool is_key3;

extern bool is_debug_keyboard;

bool Start_Keyboard_Thread(void);

void Keyboard_Thread_Join(void);

#endif
