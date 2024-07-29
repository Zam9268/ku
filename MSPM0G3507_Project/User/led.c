#include "ti_msp_dl_config.h"
#include "led.h"
volatile unsigned int delay_times = 0;

//搭配滴答定时器实现的精确ms延时
//void delay_ms(unsigned int ms)
//{
//    delay_times = ms;
//    while( delay_times != 0 );
//}

int led_init(void){
	SYSCFG_DL_init();	
	return 1;
	
}
void led_on(void)
{

//        DL_GPIO_clearPins(LED1_PORT,LED1_PIN_14_PIN);//
//        delay_ms(1000);//
//        DL_GPIO_setPins(LED1_PORT,LED1_PIN_14_PIN);  //
//        delay_ms(1000);//
}
void SysTick_Handler(void)
{
    if( delay_times != 0 )
    {
        delay_times--;
    }
}