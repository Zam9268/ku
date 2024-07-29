//#include <stdint.h>
//#include "ti_msp_dl_config.h"
//#include "LED_RGB.h"
//#include "KEY.h"
//#include "drv_oled.h"
//#include "TIME.h"
//#include "EXTI.h"
//#include "PWM.h"
//#include "SERVO.h"

///* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
//#define DELAY (8000000)

//uint8_t Key1Num;	
//int16_t i;
//int angle;


//int main(void)
//{
//    /* Power on GPIO, initialize pins as digital outputs */
//    SYSCFG_DL_init();
//	oled_init();
//	TIMG0_Init();
////	EXTI_Init();
//	PWM_Init();
//	
//	display_6_8_string(2,2,"eternal:");

//	
//   while (1) 
//	{  
//		Key1Num  =  Key_GetNum();
//		
//		display_6_8_number(50,2,angle);
//		delay_cycles(DELAY);//延时0.5秒
////		DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_0);//IO电平翻转
////		DL_GPIO_togglePins(GPIOB,DL_GPIO_PIN_22 | DL_GPIO_PIN_26);//电平翻转驱动RGB
////		 delay_cycles(DELAY);
//    }
//}
