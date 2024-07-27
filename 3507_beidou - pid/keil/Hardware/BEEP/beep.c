#include "ti_msp_dl_config.h"
#include "beep.h"

_laser_light beep;

uint8_t beep_flag =0;
uint8_t beep_time =0;
uint8_t beep_actime =0;


void BEEP_Init(void)
{
  beep.port = GPIOA;
  beep.pin = PORTA_BEEP_PIN;
  beep.period = 500; //200*5ms
  beep.light_on_percent = 0.5f;
	
  beep.reset = 1;
  beep.times = 1;
}

void laser_light_work(_laser_light *light)
{
	if(light->reset==1)
	{
		light->reset=0;
		light->cnt=0;
		light->times_cnt=0;
	}
	
	if(light->times_cnt==light->times)
	{
		light->end=1;
		return;
	}

	light->cnt++;
	if(light->cnt<=light->period*light->light_on_percent)
	{
		DL_GPIO_setPins(light->port, light->pin);
	}
	else if(light->cnt<light->period)
	{
		DL_GPIO_clearPins(light->port, light->pin);
	}
	else//完成点亮一次
	{
		light->cnt=0;
		light->times_cnt++;
	}
}


void buzzer_setup(uint32_t _period, uint16_t _times)
{
  beep.period = _period; //20*5ms
//  beep.light_on_percent = _light_on_percent;
  beep.reset = 1;
  beep.times = _times;
}

