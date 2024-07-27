#include "ti_msp_dl_config.h"

void PWM_Init(void)
{
	DL_Timer_startCounter(TIMG6);
}

void PWM_SetCompare0(uint16_t Compare)
{
	DL_TimerG_setCaptureCompareValue(TIMG6, Compare, DL_TIMER_CC_0_INDEX);
}


