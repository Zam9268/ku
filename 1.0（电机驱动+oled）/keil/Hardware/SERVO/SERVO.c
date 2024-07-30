#include "ti_msp_dl_config.h"
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

unsigned int Servo_Angle = 0;//舵机角度

/*
       配置占空比 范围 0 ~ (per-1)
   t = 0.5ms——————-舵机会转动 0 °
   t = 1.0ms——————-舵机会转动 45°
   t = 1.5ms——————-舵机会转动 90°
   t = 2.0ms——————-舵机会转动 135°
   t = 2.5ms——————-舵机会转动180°
*/


/*
 * 函 数 名 称：Set_Servo_Angle
 * 函 数 说 明：设置角度
 * 函 数 形 参：angle=要设置的角度，范围0-180
*/
void Set_Servo_Angle(unsigned int angle)
{
      uint32_t period = 2500;

      if(angle > 180)
      {
            angle = 180; // 限制角度在0到180度之间
      }

      Servo_Angle = angle;

      // 计算PWM占空比
      // 0.5ms对应的计数 = 10
      // 2.5ms对应的计数 = 50
      float min_count = 62.5f;
      float max_count = 312.5f;
      float range = max_count - min_count;
      float ServoAngle = min_count + (((float)angle / 180.0f) * range);

      DL_TimerG_setCaptureCompareValue(TIMG6, (unsigned int)(ServoAngle + 0.5f), DL_TIMER_CC_0_INDEX);
}



/*
 * 函 数 名 称：读取当前角度
 * 函 数 说 明：Get_Servo_Angle
 * 函 数 返 回：当前角度
 * 备       注：使用前必须确保之前使用过
                void Set_Servo_Angle(unsigned int angle)
                函数设置过角度
*/
unsigned int Get_Servo_Angle(void)
{
      return Servo_Angle;
}

/*
KeyNum = Key_GetNum();
		if (KeyNum == 1)				
		{
			angle += 30;				
			if (angle > 180)			
			{
				angle = 0;				
			}
		}
		Set_Servo_Angle(angle);
		display_6_8_number(50,2,angle);
*/
