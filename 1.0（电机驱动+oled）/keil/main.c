#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "LED_RGB.h"
#include "KEY.h"
#include "drv_oled.h"
#include "TIME.h"
#include "EXTI.h"
#include "PWM.h"
#include "SERVO.h"
#include "beep.h"
#include "key.h"
#include "jy62.h"
#include "lora.h"
#include "stdio.h"
#include "encoder.h"
#include "control.h"
#include "protocol.h"
#include "pid.h"
#include "openmv.h"
#include "bsp_mpu6050.h"
#include "oled.h"

/*
����0��jy62������ 
����1�� LORA����ͨ��ģ�飨Ұ����λ���ķ��ͽ���Ҳ�����棩 
����3�� openmv 
mpu6050��MPU6050_Init()�����������ʼ�� ���������õ��������ý��߾Ϳ���
protocol������ļ���Ұ����λ����Э���ļ�
����������ĸ����Ŷ������ж�4��Ƶ AC1 AC2��A�����A��B��   BC1 BC2��B�����A��B�� ֱ�Ӹ����������þͿ�����





*/
int16_t i;
int angle;
uint8_t key_num;
uint8_t str_buff1[64];
uint8_t str_buff2[64];
uint8_t str_buff3[64];
float Init_angle,Tg_angle;
uint8_t angle_flag;

int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
  SYSCFG_DL_init();
	OLED_Init();
	TIMER_Init();
	EXTI_Init();
	PWM_Init();
	jy62_Init();
	LORA_Init();
	Openmv_Init();
	protocol_init();
	PID_param_init();
//	MPU6050_Init();
	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_0);
	set_motor_enable();
	set_motor2_enable();
//	BEEP_Init();	

   while (1) 
	{             
//		key_num = Key_GetNum();
//		if(key_num ==2)
//		{			
//			//�߹̶�����100cm
//					Car_go(100);
			
			
				//�趨Ŀ��Ƕ�
//		Init_angle = Yaw;
//		Tg_angle = Init_angle +90;
//		set_pid_target(&pid_turn, Tg_angle); 
//		angle_flag = 1;
//		set_pid_target(&pid_turn_speed, 160); 


//		}
//		receiving_process();//Ұ����λ�����ܴ������ݵ���pidʱ���ע��
//		display_6_8_number_f1(5,5,Yaw);
//		display_6_8_number_f1(5,1,Tg_angle);
			DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26);
			MotorOutput(2500,2500);
			
			OLED_ShowString(100,0*16,"abc",OLED_8X16);
			OLED_ShowString(100,1*16,"abc",OLED_8X16);
			OLED_ShowString(100,2*16,"abc",OLED_8X16);
			OLED_ShowString(100,3*16,"abc",OLED_8X16);
			OLED_ShowNum(2,1,250,4,OLED_8X16);
			OLED_Update(); 
			
//			
    }
}
