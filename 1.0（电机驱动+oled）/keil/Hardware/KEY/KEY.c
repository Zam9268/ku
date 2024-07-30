#include "ti_msp_dl_config.h"
#include "key.h"
#include "system.h"



struct keys key[5] = {0};

int iButtonCount;
int iButtonFlag;
int g_nButton;    

#define keydown_port  KEYB_PORT
#define keydown_pin   KEYB_S3_PIN

#define keyup_port    KEYA_PORT
#define keyup_pin     KEYA_S2_PIN

#define KEY1   DL_GPIO_readPins(PORTB_PORT, DL_GPIO_PIN_23)
#define KEY2   DL_GPIO_readPins(PORTB_PORT, PORTB_B1_PIN)
#define KEY3   DL_GPIO_readPins(PORTB_PORT, PORTB_B2_PIN)




void keyScan(void)
{
	
	key[0].keyState = DL_GPIO_readPins(PORTB_PORT, PORTB_B5_PIN);
	key[1].keyState = DL_GPIO_readPins(PORTB_PORT, PORTB_B1_PIN);
	key[2].keyState = DL_GPIO_readPins(PORTB_PORT, PORTB_B2_PIN);
	key[3].keyState = DL_GPIO_readPins(PORTB_PORT, PORTB_B3_PIN);
	for(int i = 0;i < 4;i++)
	{
//			key[i-1].keyLongDown = 0;

		switch(key[i].keyFlag)
		{
			case 0:
			{
				if(key[i].keyState == 0)
				{
					key[i].keyFlag = 1;
					key[i].keyTime = 0;
				}
			}break;
			case 1:
			{
				if(key[i].keyState == 0)
				{
					key[i].keyFlag = 2;
				}
				else
				{
					key[i].keyFlag = 0;
				}
			}break;
			case 2:
			{
				if(key[i].keyState == 1)
				{
					key[i].keyFlag = 0;
					if(key[i].keyTime <100)
					{
						key[i].keyShortDown = 1;
					}
				}
				else
				{
					key[i].keyTime++;
					if(key[i].keyTime > 100)
					{
						key[i].keyLongDown = 1;
					}
				}
			}break;
		}
	}
}






uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if(DL_GPIO_readPins(GPIOB,PORTB_B5_PIN) == 0)
	{
		delay_ms(20);
		while(DL_GPIO_readPins(GPIOB,PORTB_B5_PIN) == 0);
		delay_ms(20);
		KeyNum = 1;
	}
	
	if(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_23) == 0)
	{
		delay_ms(20);
		while(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_23) == 0);
		delay_ms(20);
		KeyNum = 2;
	}
	
	if(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) == 0)
	{
		delay_ms(10);
		while(DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24) == 0);
		delay_ms(10);
		KeyNum = 3;
	}
	return KeyNum;
}




