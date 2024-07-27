#ifndef _KEY_H  
#define _KEY_H

#include <stdint.h>
#include <stdbool.h>

void delay_ms(uint32_t ms);
uint8_t Key_GetNum(void);


struct keys
{
	unsigned char keyFlag;
	unsigned char keyTime;
	bool keyState;
	bool keyShortDown;
	bool keyLongDown;
};
extern struct keys key[5];





 
extern int g_nButton;   //声明外部变量，方便其他地方引用。当使用定时器消抖的时候用这个,这个记录了有效按下了什么键
extern int iButtonFlag;  //记录确实按键被按下，即有效
uint8_t KEY_Scan(void);   //检测有无按键按下 




#endif