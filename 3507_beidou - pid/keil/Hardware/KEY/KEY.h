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





 
extern int g_nButton;   //�����ⲿ���������������ط����á���ʹ�ö�ʱ��������ʱ�������,�����¼����Ч������ʲô��
extern int iButtonFlag;  //��¼ȷʵ���������£�����Ч
uint8_t KEY_Scan(void);   //������ް������� 




#endif