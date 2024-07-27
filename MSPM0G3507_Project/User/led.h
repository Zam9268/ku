#ifndef led_h
#define LED_H

void delay_ms(unsigned int ms);
int led_init(void);
void led_on(void);
void SysTick_Handler(void);
#endif /* ti_msp_dl_config_h */