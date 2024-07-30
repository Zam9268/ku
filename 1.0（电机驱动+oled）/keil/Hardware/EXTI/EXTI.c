#include "ti_msp_dl_config.h"
#include "encoder.h"

volatile uint32_t gpioB;
volatile uint16_t CountSensor_Count;

void EXTI_Init(void)
{
	NVIC_ClearPendingIRQ(PORTB_INT_IRQN);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

