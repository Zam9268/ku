#ifndef _TIME_H  
#define _TIME_H


extern int32_t actual_speed1;
extern int16_t down_num;

void TIMER_Init(void);
void TIMG0_IRQHandler(void);
void TIMA0_IRQHandler(void);

#endif