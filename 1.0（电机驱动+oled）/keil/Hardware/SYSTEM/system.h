#ifndef _SYSTEM_H  
#define _SYSTEM_H

#include <stdint.h>

void SystickInit(void);

uint32_t micros(void);
uint32_t millis(void);
void Delay_Ms(uint32_t x);
void delay_ms(uint32_t x);
void delay_us(uint32_t x);
void Delay_Us(uint32_t x);

typedef struct
{
  volatile float last_time;
  volatile float current_time;
  volatile float period;
  volatile uint16_t period_int;//µ¥Î»ms
}systime;


void 	get_systime(systime *sys);
float get_systime_ms(void);
uint32_t get_systick_ms(void);


#endif