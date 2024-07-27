#include "ti_msp_dl_config.h"

void RGB_OFF(void)
{
	DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26 | DL_GPIO_PIN_27);
}

void RGB_ON(void)
{
	DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26 | DL_GPIO_PIN_27);
}

void RGB_Toggle(void)
{
	DL_GPIO_togglePins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26 | DL_GPIO_PIN_27);//°×µÆ
}

void LED_ON(void)
{
	DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);
}


void LED_OFF(void)
{
	DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_0);
}


void LED_Toggle(void)
{
	DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
}


