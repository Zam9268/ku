#ifndef _EXTI_H  
#define _EXTI_H

#include <stdint.h>


void EXTI_Init(void);
uint16_t CountSensor_Get(void);
void GROUP1_IRQHandler(void);

#endif