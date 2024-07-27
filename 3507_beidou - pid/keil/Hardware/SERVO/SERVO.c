#include "ti_msp_dl_config.h"
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

unsigned int Servo_Angle = 0;//����Ƕ�

/*
       ����ռ�ձ� ��Χ 0 ~ (per-1)
   t = 0.5ms������������-�����ת�� 0 ��
   t = 1.0ms������������-�����ת�� 45��
   t = 1.5ms������������-�����ת�� 90��
   t = 2.0ms������������-�����ת�� 135��
   t = 2.5ms������������-�����ת��180��
*/


/*
 * �� �� �� �ƣ�Set_Servo_Angle
 * �� �� ˵ �������ýǶ�
 * �� �� �� �Σ�angle=Ҫ���õĽǶȣ���Χ0-180
*/
void Set_Servo_Angle(unsigned int angle)
{
      uint32_t period = 2500;

      if(angle > 180)
      {
            angle = 180; // ���ƽǶ���0��180��֮��
      }

      Servo_Angle = angle;

      // ����PWMռ�ձ�
      // 0.5ms��Ӧ�ļ��� = 10
      // 2.5ms��Ӧ�ļ��� = 50
      float min_count = 62.5f;
      float max_count = 312.5f;
      float range = max_count - min_count;
      float ServoAngle = min_count + (((float)angle / 180.0f) * range);

      DL_TimerG_setCaptureCompareValue(TIMG6, (unsigned int)(ServoAngle + 0.5f), DL_TIMER_CC_0_INDEX);
}



/*
 * �� �� �� �ƣ���ȡ��ǰ�Ƕ�
 * �� �� ˵ ����Get_Servo_Angle
 * �� �� �� �أ���ǰ�Ƕ�
 * ��       ע��ʹ��ǰ����ȷ��֮ǰʹ�ù�
                void Set_Servo_Angle(unsigned int angle)
                �������ù��Ƕ�
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
